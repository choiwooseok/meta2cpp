#include "User.h"

namespace test {
namespace examples {

std::string User::getId() {
  return id;
}

void User::setId(const std::string& id) {
  this->id = id;
}

std::string User::getEmail() {
  return email;
}

void User::setEmail(const std::string& email) {
  this->email = email;
}

std::string User::getUsername() {
  return username;
}

void User::setUsername(const std::string& username) {
  this->username = username;
}

std::string User::getPassword() {
  return password;
}

void User::setPassword(const std::string& password) {
  this->password = password;
}

std::shared_ptr<Role> User::getRole() {
  return role;
}

void User::setRole(std::shared_ptr<Role> role) {
  this->role = role;
}

std::string User::toString() {
  std::string sb = "";
  sb += "{";
  sb += "\"id\" : ";
  sb += "\"" + id + "\"";
  sb += ",";
  sb += "\"email\" : ";
  sb += "\"" + email + "\"";
  sb += ",";
  sb += "\"username\" : ";
  sb += "\"" + username + "\"";
  sb += ",";
  sb += "\"password\" : ";
  sb += "\"" + password + "\"";
  sb += ",";
  sb += "\"role\" : ";
  if(role != nullptr) {
    sb += role->toString();
  } else {
    sb += "null";
  }
  sb += ",";
  sb.pop_back();
  sb += "}";
  return sb;
}

void User::fromJson(boost::property_tree::ptree& json) {
  if(json.find("id") != json.not_found()) {
    std::string id_ = json.get<std::string>("id");
    setId(id_);
  }
  if(json.find("email") != json.not_found()) {
    std::string email_ = json.get<std::string>("email");
    setEmail(email_);
  }
  if(json.find("username") != json.not_found()) {
    std::string username_ = json.get<std::string>("username");
    setUsername(username_);
  }
  if(json.find("password") != json.not_found()) {
    std::string password_ = json.get<std::string>("password");
    setPassword(password_);
  }
  if(json.find("role") != json.not_found()) {
    boost::property_tree::ptree role_ = json.get_child("role");
    if(role == nullptr) {
      role = std::make_shared<Role>();
    }
    role->fromJson(role_);
  }
}

} /* namespace test */
} /* namespace examples */

