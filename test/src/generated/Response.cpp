#include "Response.h"

namespace test {
namespace examples {

std::string Response::getCode() {
    return code;
}

void Response::setCode(const std::string& code) {
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
    sb += "code : ";
    sb += code;
    sb += ",";
    sb += "name : ";
    sb += name;
    sb += ",";
    sb += "desc : ";
    sb += desc;
    sb += ",";
    sb.pop_back();
    return sb;
}

void Response::fromJson(boost::property_tree::ptree& json) {
    std::string code_ = json.get<std::string>("code");
    setCode(code_);
    std::string name_ = json.get<std::string>("name");
    setName(name_);
    std::string desc_ = json.get<std::string>("desc");
    setDesc(desc_);
}

} /* namespace test */
} /* namespace examples */

