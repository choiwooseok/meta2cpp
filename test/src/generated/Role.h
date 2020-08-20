#ifndef ROLE_H_
#define ROLE_H_

#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace test {
namespace examples {

class Role {
public:
  Role() = default;
  Role(const Role&) = default;
  Role(Role&&) = default;
  Role& operator=(const Role&) = default;
  Role& operator=(Role&&) = default;
  virtual ~Role() = default;

private:
  /**
  * fieldName : roleId
  * fieldDesc : roleId
  */
  std::string roleId;

public:
  std::string getRoleId();
  void setRoleId(const std::string& roleid);

private:
  /**
  * fieldName : roleName
  * fieldDesc : roleName
  */
  std::string roleName;

public:
  std::string getRoleName();
  void setRoleName(const std::string& rolename);

private:
  /**
  * fieldName : available
  * fieldDesc : 비밀번호
  */
  std::string available;

public:
  std::string getAvailable();
  void setAvailable(const std::string& available);

public:
  virtual std::string toString();
  void fromJson(boost::property_tree::ptree& json);
};
} /* namespace test */
} /* namespace examples */

#endif /* ROLE_H_ */
