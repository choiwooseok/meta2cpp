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

bool Response::getExcept() {
    return except;
}

void Response::setExcept(bool except) {
    this->except = except;
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
    sb += "\"except\" : ";
    sb += "\"" +  std::to_string(except) + "\"";
    sb += ",";
    sb.pop_back();
    sb += "}";
    return sb;
}

void Response::fromJson(boost::property_tree::ptree& json) {
    int code_ = json.get<int>("code");
    setCode(code_);
    std::string name_ = json.get<std::string>("name");
    setName(name_);
    std::string desc_ = json.get<std::string>("desc");
    setDesc(desc_);
    bool except_ = json.get<bool>("except");
    setExcept(except_);
}

} /* namespace test */
} /* namespace examples */

