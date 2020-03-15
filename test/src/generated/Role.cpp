#include "Role.h"

namespace test {
namespace examples {

std::string Role::getRoleId() {
    return roleId;
}

void Role::setRoleId(const std::string& roleid) {
    this->roleId = roleid;
}

std::string Role::getRoleName() {
    return roleName;
}

void Role::setRoleName(const std::string& rolename) {
    this->roleName = rolename;
}

std::string Role::getAvailable() {
    return available;
}

void Role::setAvailable(const std::string& available) {
    this->available = available;
}

std::string Role::toString() {
    std::string sb = "";
    sb += "{";
    sb += "\"roleId\" : ";
    sb += "\"" + roleId + "\"";
    sb += ",";
    sb += "\"roleName\" : ";
    sb += "\"" + roleName + "\"";
    sb += ",";
    sb += "\"available\" : ";
    sb += "\"" + available + "\"";
    sb += ",";
    sb.pop_back();
    sb += "}";
    return sb;
}

void Role::fromJson(boost::property_tree::ptree& json) {
    std::string roleId_ = json.get<std::string>("roleId");
    setRoleId(roleId_);
    std::string roleName_ = json.get<std::string>("roleName");
    setRoleName(roleName_);
    std::string available_ = json.get<std::string>("available");
    setAvailable(available_);
}

} /* namespace test */
} /* namespace examples */

