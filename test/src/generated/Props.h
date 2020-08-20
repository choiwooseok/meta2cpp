#ifndef PROPS_H_
#define PROPS_H_

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace test {
namespace examples {

class Props {
public:
  Props() = default;
  Props(const Props&) = default;
  Props(Props&&) = default;
  Props& operator=(const Props&) = default;
  Props& operator=(Props&&) = default;
  virtual ~Props() = default;

private:
  /**
  * fieldName : empno
  * fieldDesc : 사번
  */
  std::string empno;

public:
  std::string getEmpno();
  void setEmpno(const std::string& empno);

private:
  /**
  * fieldName : salary
  * fieldDesc : 임금
  */
  std::string salary;

public:
  std::string getSalary();
  void setSalary(const std::string& salary);

private:
  /**
  * fieldName : ename
  * fieldDesc : 이름
  */
  std::string ename;

public:
  std::string getEname();
  void setEname(const std::string& ename);

private:
  /**
  * fieldName : dept
  * fieldDesc : 부서
  */
  std::string dept;

public:
  std::string getDept();
  void setDept(const std::string& dept);

public:
  virtual std::string toString();
  void fromJson(boost::property_tree::ptree& json);
};
} /* namespace test */
} /* namespace examples */

#endif /* PROPS_H_ */
