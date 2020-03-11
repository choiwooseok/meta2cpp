#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>

namespace meta2Cpp {

class Generator {
private:
    static constexpr const char* TAP  = "    ";
    static constexpr const char* ENDL = "\n";

private:
    std::string metaPath;
    std::string outputPath;

    boost::property_tree::ptree meta;

    std::string className;
    std::vector<std::string> ns;

    std::unordered_map<std::string, std::string> cppTypes = {
        {"bool", "bool"},
        {"char", "char"},
        {"wchar_t", "wchar_t"},
        {"unsigned char", "unsigned char"},
        {"short", "short"},
        {"unsigned short", "unsigned short"},
        {"int", "int"},
        {"unsigned int", "unsigned int"},
        {"double", "double"},
        {"float", "float"},
        {"long", "long"},
        {"unsigned long", "unsigned long"},
        {"string", "std::string"}    
    };

private:

    std::string getCppType(const std::string& metaTypeName) {
        if(cppTypes.find(metaTypeName) != cppTypes.end()) {
            return cppTypes[metaTypeName];
        } else {
            return "std::shared_ptr<" + metaTypeName + ">";
        }
    }

    void startHeaderGuard(std::ofstream& fs, const std::string& classNameUpper) {
        fs << "#ifndef " << classNameUpper << "_H_" << ENDL;
        fs << "#define " << classNameUpper << "_H_" << ENDL << ENDL;
    }

    void endHeaderGuard(std::ofstream& fs, const std::string& classNameUpper) {
        fs << "#endif /* " << classNameUpper << "_H_ */" << ENDL;
    }

    void startNamespace(std::ofstream& fs) {
        if(!ns.empty()) {
            for(std::string& elem : ns) {
                fs << "namespace " << elem << " {" << ENDL;
            }
            fs << ENDL;
        }
    }

    void endNamespace(std::ofstream& fs) {
        if(!ns.empty()) {
            for(std::string& elem : ns) {
                fs << "} /* namespace " << elem << " */" << ENDL;
            }
            fs << ENDL;
        }
    }

    void startClass(std::ofstream& fs, const std::string& parentClassName) {
        fs << "class " << className;
        if(!parentClassName.empty()) {
            fs << ": public " << parentClassName << " {";
        } else {
            fs << " {";
        }
        fs << ENDL;
    }

    void endClass(std::ofstream& fs) {
        fs << "};" << ENDL;
    }

    void ruleOfZero(std::ofstream& fs) {
        fs << "public:" << ENDL;
        fs << TAP << className << "() = default;" << ENDL;
        fs << TAP << className << "(const " << className << "&) = default;" << ENDL;
        fs << TAP << className << "(" << className << "&&) = default;" << ENDL;
        fs << TAP << className << "& operator=(const " << className << "&) = default;" << ENDL;
        fs << TAP << className << "& operator=(" << className << "&&) = default;" << ENDL;
        fs << TAP << "virtual ~"<< className << "() = default;" << ENDL << ENDL;
    }

public:
    // UTILITY FUNCTIONS
    std::string toUpper(const std::string& str) {
        std::string ret;
        std::transform(str.begin(), str.end(), std::back_inserter(ret), ::toupper);
        return ret;
    }

    std::string toLower(const std::string& str) {
        std::string ret;
        std::transform(str.begin(), str.end(), std::back_inserter(ret), ::tolower);
        return ret;
    }

    std::string capitalize(const std::string& str) {
        std::string ret(str);
        ret[0] = ::toupper(ret[0]);
        return ret;
    }

    bool starts_with(const std::string &src, const std::string& starting) {
        return src.length() >= starting.length() ? (0 == src.compare(0, starting.length(), starting)) : false;
    }

    bool ends_with(const std::string& src, const std::string& ending) {
        return src.length() >= ending.length() ? (0 == src.compare(src.length() - ending.length(), ending.length(), ending)) : false;
    }

public:
    Generator(const std::string& metaPath, const std::string& outputPath)
        : metaPath(metaPath), outputPath(outputPath) {

        if(!ends_with(outputPath, "/")) {
            this->outputPath += "/";
        }

        try {
            boost::property_tree::read_json(metaPath, meta);        
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        className = meta.get<std::string>("class-name");
        for(auto& elem : meta.get_child("namespaces")) {
            ns.push_back(elem.second.data());
        };
    }

    void generateHeader() {
        std::ofstream fs(outputPath + className + ".h");
        std::string classNameUpper = toUpper(className);
        std::string parentClassName = meta.get<std::string>("parent-class-name", "");
        boost::property_tree::ptree fields = meta.get_child("fields");
        boost::property_tree::ptree includes = meta.get_child("includes");

        startHeaderGuard(fs, classNameUpper);
        for(auto include : includes) {
            fs << "#include <" << include.second.data() << ">" <<ENDL;
        }
        fs << ENDL;

        startNamespace(fs);

        startClass(fs, parentClassName);

        ruleOfZero(fs);

        for(auto field : fields) {
            // FIELD INFOS 
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");

            // GENERATE HELPER
            std::string fieldNameUpper1st = capitalize(fieldName);

            // FIELD DECLARATION
            fs << "private:" << ENDL;
            fs << TAP << "/**" << ENDL;
            fs << TAP << "* fieldName : " << fieldName << ENDL;
            fs << TAP << "* fieldDesc : " << field.second.get<std::string>("description", "") << ENDL;
            fs << TAP << "*/" << ENDL;
            if(isArray) {
                fs << TAP << "std::vector< " << fieldCppType << " > " << fieldName << ";";
            } else {
                fs << TAP << fieldCppType << " " << fieldName << ";";
            }
            fs << ENDL << ENDL;

            // GETTER & SETTER
            fs << "public:" << ENDL;
            if(isArray) {
                fs << TAP << "std::vector< " << fieldCppType << " >& get" << fieldNameUpper1st << "();" << ENDL;
                fs << TAP << "void set" << fieldNameUpper1st << "(const std::vector< " << fieldCppType << " >& " << toLower(fieldName) << ");" << ENDL;
            } else {
                fs << TAP << fieldCppType << " get" << fieldNameUpper1st << "();" << ENDL;
                std::string setterParamStr = "";
                if(fieldCppType == "std::string") {
                    setterParamStr = "const std::string& " + toLower(fieldName);
                } else {
                    setterParamStr = fieldCppType + " " + toLower(fieldName);
                }
                fs << TAP << "void " << "set" << fieldNameUpper1st << "(" << setterParamStr << ");" << ENDL << ENDL;
            }
        }

        // COMMON METHODS
        fs << "public:" << ENDL;
        fs << TAP << "virtual std::string toString();" << ENDL;

        endClass(fs);

        endNamespace(fs);

        endHeaderGuard(fs, classNameUpper);
        fs.close();
    }

    void generateSource() {
        std::ofstream fs(outputPath + className + ".cpp");
        fs << "#include \"" << className << ".h\"" << ENDL << ENDL;

        startNamespace(fs);

        boost::property_tree::ptree fields = meta.get_child("fields");
        for(auto field : fields) {
            // FIELD INFOS 
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");
            std::string fieldNameUpper1st = capitalize(fieldName);

            // GETTER & SETTER
            if(isArray) {
                fs << "std::vector< " << fieldCppType << " >& " << className <<"::get" << fieldNameUpper1st << "() {" << ENDL;
                fs << TAP << "return " << fieldName << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

                fs << "void " << className << "::set" << fieldNameUpper1st << "(const std::vector< " << fieldCppType << " >& " << toLower(fieldName) << ") {" << ENDL;
                fs << TAP << "this->" << fieldName << " = " << toLower(fieldName) << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

            } else {
                fs << fieldCppType << " " << className << "::get" << fieldNameUpper1st << "() {" << ENDL;
                fs << TAP << "return " << fieldName << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

                std::string setterParamStr = "";
                if(fieldCppType == "std::string") {
                    setterParamStr = "const std::string& " + toLower(fieldName);
                } else {
                    setterParamStr = fieldCppType + " " + toLower(fieldName);
                }
                fs << "void " << className << "::set" << fieldNameUpper1st << "(" << setterParamStr << ") {" << ENDL;
                fs << TAP << "this->" << fieldName << " = " << toLower(fieldName) << ";" << ENDL;
                fs << "}" << ENDL << ENDL;
            }
        }

        // COMMON METHODS
        fs << "std::string " << className << "::toString() {" << ENDL;
        fs << TAP << "std::string sb = \"\";" << ENDL; 
        for(auto field : fields) {
            // FIELD INFOS 
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");

            fs << TAP << "sb += \"" << fieldName << " : \"" << ";" << ENDL;
            if(isArray) {
                fs << TAP << "sb += \"[\";"<< ENDL;
                fs << TAP << "for(auto elem : " << fieldName << ") {" << ENDL;
                if(fieldCppType == "std::string") {
                    fs << TAP << TAP << "sb += elem;" << ENDL;
                } else if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAP << TAP << "sb += elem->toString();" << ENDL;
                } else {
                    fs << TAP << TAP << "sb += std::to_string(elem);" << ENDL;
                }
                fs << TAP << TAP << "sb += \",\";" << ENDL;
                fs << TAP << "}" << ENDL;
                fs << TAP << "sb.pop_back();" << ENDL;
                fs << TAP << "sb += \"]\";"<< ENDL;
            } else {
                if(fieldCppType == "std::string") {
                    fs << TAP << "sb += " << fieldName << ";" << ENDL;
                } else if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAP << "sb += " << fieldName << "->toString();" << ENDL;
                } else {
                    fs << TAP << "sb += std::to_string(" << fieldName << ");" << ENDL;
                }
            }
            fs << TAP << "sb += \",\";" << ENDL;
        }
        fs << TAP << "sb.pop_back();" << ENDL;
        fs << TAP << "return sb;" << ENDL; 
        fs << "}" << ENDL << ENDL;

        endNamespace(fs);
        fs.close();
    }
};

} /* namespace meta2Cpp */
#endif