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
    std::string meTABath;
    std::string outputPath;

    boost::property_tree::ptree meta;

    std::string className;
    std::string classNameUpper;
    std::string parentClassName;

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
        {"string", "std::string"},    
        {"wstring", "std::wstring"}
    };

private:
    std::string TAB;
    static constexpr const char* ENDL = "\n";

private:

    std::string getCppType(const std::string& metaTypeName) {
        if(cppTypes.find(metaTypeName) != cppTypes.end()) {
            return cppTypes[metaTypeName];
        } else {
            return "std::shared_ptr<" + metaTypeName + ">";
        }
    }

    void startHeaderGuard(std::ofstream& fs) {
        fs << "#ifndef " << classNameUpper << "_H_" << ENDL;
        fs << "#define " << classNameUpper << "_H_" << ENDL << ENDL;
    }

    void endHeaderGuard(std::ofstream& fs) {
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

    void startClass(std::ofstream& fs) {
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
        fs << TAB << className << "() = default;" << ENDL;
        fs << TAB << className << "(const " << className << "&) = default;" << ENDL;
        fs << TAB << className << "(" << className << "&&) = default;" << ENDL;
        fs << TAB << className << "& operator=(const " << className << "&) = default;" << ENDL;
        fs << TAB << className << "& operator=(" << className << "&&) = default;" << ENDL;
        fs << TAB << "virtual ~"<< className << "() = default;" << ENDL << ENDL;
    }

    void generateGetterSetter(std::ofstream& fs, boost::property_tree::ptree& fields) {
        for(auto field : fields) {
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");
            std::string fieldNameUpper1st = capitalize(fieldName);

            if(isArray) {
                fs << "std::vector< " << fieldCppType << " >& " << className <<"::get" << fieldNameUpper1st << "() {" << ENDL;
                fs << TAB << "return " << fieldName << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

                fs << "void " << className << "::set" << fieldNameUpper1st << "(const std::vector< " << fieldCppType << " >& " << toLower(fieldName) << ") {" << ENDL;
                fs << TAB << "this->" << fieldName << " = " << toLower(fieldName) << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

            } else {
                fs << fieldCppType << " " << className << "::get" << fieldNameUpper1st << "() {" << ENDL;
                fs << TAB << "return " << fieldName << ";" << ENDL;
                fs << "}" << ENDL << ENDL;

                std::string setterParamStr = "";
                if(fieldCppType == "std::string") {
                    setterParamStr = "const std::string& " + toLower(fieldName);
                } else {
                    setterParamStr = fieldCppType + " " + toLower(fieldName);
                }
                fs << "void " << className << "::set" << fieldNameUpper1st << "(" << setterParamStr << ") {" << ENDL;
                fs << TAB << "this->" << fieldName << " = " << toLower(fieldName) << ";" << ENDL;
                fs << "}" << ENDL << ENDL;
            }
        }
    }

    void generateToString(std::ofstream& fs, boost::property_tree::ptree& fields) {
        fs << "std::string " << className << "::toString() {" << ENDL;
        fs << TAB << "std::string sb = \"\";" << ENDL; 
        fs << TAB << "sb += \"{\";"<< ENDL;
        for(auto field : fields) {
            // FIELD INFOS 
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");

            fs << TAB << "sb += \"" << "\\\"" << fieldName << "\\\"" << " : \";" << ENDL;
            if(isArray) {
                fs << TAB << "sb += \"[\";"<< ENDL;
                fs << TAB << "for(auto elem : " << fieldName << ") {" << ENDL;
                if(fieldCppType == "std::string") {
                    fs << TAB << TAB << "sb += \"\\\"\" + " << "elem" << " + \"\\\"\";" << ENDL;
                } else if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAB << TAB << "sb += elem->toString();" << ENDL;
                } else {
                    fs << TAB << TAB << "sb += \"\\\"\" + " << "std::to_string(elem)" << " + \"\\\"\";" << ENDL;
                }
                fs << TAB << TAB << "sb += \",\";" << ENDL;
                fs << TAB << "}" << ENDL;
                fs << TAB << "sb.pop_back();" << ENDL;
                fs << TAB << "sb += \"]\";"<< ENDL;
            } else {
                if(fieldCppType == "std::string") {
                    fs << TAB << "sb += \"\\\"\" + " << fieldName << " + \"\\\"\";" << ENDL;
                } else if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAB << "if(" << fieldName << " != nullptr) {" << ENDL;
                    fs << TAB << TAB << "sb += " << fieldName << "->toString();" << ENDL;
                    fs << TAB << "} else {" << ENDL;
                    fs << TAB << TAB << "sb += \"null\";" << ENDL;
                    fs << TAB << "}" << ENDL;
                } else {
                    fs << TAB << "sb += \"\\\"\" + " << " std::to_string(" << fieldName << ")" << " + \"\\\"\";" << ENDL;
                }
            }
            fs << TAB << "sb += \",\";" << ENDL;
        }
        fs << TAB << "sb.pop_back();" << ENDL;
        fs << TAB << "sb += \"}\";"<< ENDL;
        fs << TAB << "return sb;" << ENDL; 
        fs << "}" << ENDL << ENDL;
    }

    void generateFromJson(std::ofstream& fs, boost::property_tree::ptree& fields) {
        fs << "void " << className << "::fromJson(boost::property_tree::ptree& json) {" << ENDL;
        for(auto field : fields) {
            // FIELD INFOS 
            std::string fieldName = field.second.get<std::string>("fieldName");
            std::string fieldCppType = getCppType(field.second.get<std::string>("fieldType"));
            bool isArray = field.second.get<bool>("isArray");
            std::string fieldNameUpper1st = capitalize(fieldName);

            if(isArray) {
                if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAB << "if(json.find(\"" << fieldName << "\") != json.not_found()) {" << ENDL;
                    fs << TAB << TAB << "for(auto elem : json.get_child(\"" << fieldName << "\")) {" << ENDL;
                    fs << TAB << TAB << TAB << fieldCppType << " elem_ptr = std::make_shared<" << field.second.get<std::string>("fieldType") << ">();" << ENDL;
                    fs << TAB << TAB << TAB << "elem_ptr->fromJson(elem);" << ENDL;
                    fs << TAB << TAB << TAB << fieldName << ".push_back(elem_ptr);" << ENDL;
                    fs << TAB << TAB << "}" << ENDL;
                    fs << TAB << "}" << ENDL;
                } else {
                    fs << TAB << "if(json.find(\"" << fieldName << "\") != json.not_found()) {" << ENDL;
                    fs << TAB << TAB << "for(auto elem : json.get_child(\"" << fieldName << "\")) {" << ENDL;
                    fs << TAB << TAB << TAB << fieldName << ".push_back(elem.second.get_value<" << fieldCppType << ">());" << ENDL;
                    fs << TAB << TAB << "}" << ENDL;
                    fs << TAB << "}" << ENDL;
                }

            } else {
                if(starts_with(fieldCppType, "std::shared")) {
                    fs << TAB << "if(json.find(\"" << fieldName << "\") != json.not_found()) {" << ENDL;
                    fs << TAB << TAB << "boost::property_tree::ptree " << fieldName << "_ = " << "json.get_child(\"" << fieldName << "\");" << ENDL;
                    fs << TAB << TAB << "if(" << fieldName << " == nullptr) {" << ENDL;
                    fs << TAB << TAB << TAB << fieldName << " = std::make_shared<" << field.second.get<std::string>("fieldType") << ">();" << ENDL;
                    fs << TAB << TAB << "}" << ENDL;
                    fs << TAB << TAB << fieldName << "->fromJson(" << fieldName << "_);" << ENDL;
                    fs << TAB << "}" << ENDL;
                } else {
                    fs << TAB << "if(json.find(\"" << fieldName << "\") != json.not_found()) {" << ENDL;
                    fs << TAB << TAB << fieldCppType << " " << fieldName << "_ = json.get<" << fieldCppType << ">(\"" << fieldName << "\");" << ENDL;
                    fs << TAB << TAB << "set" << fieldNameUpper1st << "(" << fieldName << "_);" << ENDL;
                    fs << TAB << "}" << ENDL;
                }
            }
        }
        fs << "}" << ENDL << ENDL;
    }

public:
    Generator(const std::string& meTABath, const std::string& outputPath, int TABSize = 2)
        : meTABath(meTABath), outputPath(outputPath) {
        TAB = std::string(TABSize, ' ');
        if(!ends_with(outputPath, "/")) {
            this->outputPath += "/";
        }

        boost::property_tree::read_json(meTABath, meta);        

        className = meta.get<std::string>("class-name");
        classNameUpper = toUpper(className);
        parentClassName = meta.get<std::string>("parent-class-name", "");
        for(auto& elem : meta.get_child("namespaces")) {
            ns.push_back(elem.second.data());
        };
    }

    void generateHeader() {
        std::ofstream fs(outputPath + className + ".h");
        boost::property_tree::ptree fields = meta.get_child("fields");
        boost::property_tree::ptree includes = meta.get_child("includes");

        startHeaderGuard(fs);
        for(auto include : includes) {
            fs << "#include <" << include.second.data() << ">" << ENDL;
        }
        fs << ENDL;

        startNamespace(fs);

        startClass(fs);

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
            fs << TAB << "/**" << ENDL;
            fs << TAB << "* fieldName : " << fieldName << ENDL;
            fs << TAB << "* fieldDesc : " << field.second.get<std::string>("description", "") << ENDL;
            fs << TAB << "*/" << ENDL;
            if(isArray) {
                fs << TAB << "std::vector< " << fieldCppType << " > " << fieldName << ";";
            } else {
                fs << TAB << fieldCppType << " " << fieldName << ";";
            }
            fs << ENDL << ENDL;

            // GETTER & SETTER
            fs << "public:" << ENDL;
            if(isArray) {
                fs << TAB << "std::vector< " << fieldCppType << " >& get" << fieldNameUpper1st << "();" << ENDL;
                fs << TAB << "void set" << fieldNameUpper1st << "(const std::vector< " << fieldCppType << " >& " << toLower(fieldName) << ");" << ENDL;
            } else {
                fs << TAB << fieldCppType << " get" << fieldNameUpper1st << "();" << ENDL;
                std::string setterParamStr = "";
                if(fieldCppType == "std::string") {
                    setterParamStr = "const std::string& " + toLower(fieldName);
                } else {
                    setterParamStr = fieldCppType + " " + toLower(fieldName);
                }
                fs << TAB << "void " << "set" << fieldNameUpper1st << "(" << setterParamStr << ");" << ENDL << ENDL;
            }
        }

        // COMMON METHODS
        fs << "public:" << ENDL;
        fs << TAB << "virtual std::string toString();" << ENDL;
        fs << TAB << "void fromJson(boost::property_tree::ptree& json);" << ENDL;

        endClass(fs);

        endNamespace(fs);

        endHeaderGuard(fs);
        fs.close();
    }

    void generateSource() {
        std::ofstream fs(outputPath + className + ".cpp");
        fs << "#include \"" << className << ".h\"" << ENDL << ENDL;

        startNamespace(fs);

        boost::property_tree::ptree fields = meta.get_child("fields");

        generateGetterSetter(fs, fields);
        generateToString(fs, fields);
        generateFromJson(fs, fields);

        endNamespace(fs);
        fs.close();
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
};

} /* namespace meta2Cpp */
#endif