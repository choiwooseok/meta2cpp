#include "Response.h"

namespace test {
namespace examples {

int Response::getCode() {
    return code;
}

void Response::setCode(int code) {
    this->code = code;
}

std::string Response::getName() {
    return name;
}

void Response::setName(const std::string& name) {
    this->name = name;
}

std::string Response::getDesc() {
    return desc;
}

void Response::setDesc(const std::string& desc) {
    this->desc = desc;
}

std::string Response::toString() {
    std::string sb = "";
    sb += "{";
    sb += "\"code\" : ";
    sb += "\"" +  std::to_string(code) + "\"";
    sb += ",";
    sb += "\"name\" : ";
    sb += "\"" + name + "\"";
    sb += ",";
    sb += "\"desc\" : ";
    sb += "\"" + desc + "\"";
    sb += ",";
    sb.pop_back();
    sb += "}";
    return sb;
}

void Response::fromJson(boost::property_tree::ptree& json) {
    if(json.find("code") != json.not_found()) {
        int code_ = json.get<int>("code");
        setCode(code_);
    }
    if(json.find("name") != json.not_found()) {
        std::string name_ = json.get<std::string>("name");
        setName(name_);
    }
    if(json.find("desc") != json.not_found()) {
        std::string desc_ = json.get<std::string>("desc");
        setDesc(desc_);
    }
}

} /* namespace test */
} /* namespace examples */

