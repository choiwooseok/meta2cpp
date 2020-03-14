#ifndef USER_H_
#define USER_H_

#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <Role.h>

namespace test {
namespace examples {

class User {
public:
    User() = default;
    User(const User&) = default;
    User(User&&) = default;
    User& operator=(const User&) = default;
    User& operator=(User&&) = default;
    virtual ~User() = default;

private:
    /**
    * fieldName : id
    * fieldDesc : id
    */
    std::string id;

public:
    std::string getId();
    void setId(const std::string& id);

private:
    /**
    * fieldName : email
    * fieldDesc : email
    */
    std::string email;

public:
    std::string getEmail();
    void setEmail(const std::string& email);

private:
    /**
    * fieldName : username
    * fieldDesc : 이름
    */
    std::string username;

public:
    std::string getUsername();
    void setUsername(const std::string& username);

private:
    /**
    * fieldName : password
    * fieldDesc : 비밀번호
    */
    std::string password;

public:
    std::string getPassword();
    void setPassword(const std::string& password);

private:
    /**
    * fieldName : role
    * fieldDesc : role
    */
    std::shared_ptr<Role> role;

public:
    std::shared_ptr<Role> getRole();
    void setRole(std::shared_ptr<Role> role);

public:
    virtual std::string toString();
    void fromJson(boost::property_tree::ptree& json);
};
} /* namespace test */
} /* namespace examples */

#endif /* USER_H_ */
