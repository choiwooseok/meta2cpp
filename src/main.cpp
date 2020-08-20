#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "Generator.hpp"

int main(int argc, char** argv) {
    try {
        namespace opt = boost::program_options;
        opt::options_description desc("Allowed options");
        desc.add_options()
            ("help", "Argv :")
            ("input,i", opt::value<std::string>()->required(), "<arg> input meta path")
            ("output,o", opt::value<std::string>()->required(), "<arg> output dir");

        opt::variables_map vm;
        opt::store(opt::parse_command_line(argc, argv, desc), vm);
        opt::notify(vm);
        
        if(vm.count("help") || argc == 1) {
            std::cout << desc << std::endl;
            return 0;
        }
        std::string in = vm["input"].as<std::string>();
        std::string out = vm["output"].as<std::string>();

        if(!boost::filesystem::exists(out)) {
            throw std::runtime_error("output dir does not exists");
        }
        
        using namespace meta2Cpp;
        Generator g(in, out);
        // Generator g(in, out, 4);
        g.generateHeader();
        g.generateSource();
    } catch (std::exception& e) {
        std::cerr << "codeGen Failed cause : " << std::endl;        
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "codeGen Failed" << std::endl;        
        return -1;
    }

    return 0;
}