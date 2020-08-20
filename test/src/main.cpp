#include <iostream>
#include <sstream>
#include <memory>
#include <Props.h>
#include <User.h>
#include <Role.h>
#include <Response.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace test::examples;

boost::property_tree::ptree jsonStrToPtree(const std::string& jsonStr) {
    boost::property_tree::ptree pt;
    std::stringstream ss(jsonStr);
    boost::property_tree::read_json(ss, pt);
    return pt;
}

std::shared_ptr<Response> foo(std::shared_ptr<User> target) {
    std::cout << target->toString() << std::endl;
    /**
     * Do Something;
     */
    std::shared_ptr<Response> response = std::make_shared<Response>();
    response->setCode(200);
    response->setName("OK");
    response->setDesc("NORMAL");
    return response;
}

void useCaseMessageProps() {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("../src/lang/en.json", pt);

    Props props;
    props.fromJson(pt);
    std::cout << props.getEname() << std::endl;

    pt.clear();
    boost::property_tree::read_json("../src/lang/kr.json", pt);
    props.fromJson(pt);
    std::cout << props.getEname() << std::endl;
}

int main(int argc, char** argv) {
    useCaseMessageProps();

    std::string userJson = R"(
        {
            "id" : "1",
            "email" : "admin@admin",
            "username" : "admin",
            "password" : "admin",
            "role" : {
                "roleId" : "ADMIN",
                "roleName" : "ADMIN",
                "available" : "all"
            }
        }
    )";
    boost::property_tree::ptree pt = jsonStrToPtree(userJson);
    std::shared_ptr<User> user = std::make_shared<User>();
    user->fromJson(pt);
    std::shared_ptr<Response> ret = foo(user);
    std::cout << ret->toString() << std::endl;
    return 0;
}