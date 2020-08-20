#include "Props.h"

namespace test {
namespace examples {

std::string Props::getEmpno() {
  return empno;
}

void Props::setEmpno(const std::string& empno) {
  this->empno = empno;
}

std::string Props::getSalary() {
  return salary;
}

void Props::setSalary(const std::string& salary) {
  this->salary = salary;
}

std::string Props::getEname() {
  return ename;
}

void Props::setEname(const std::string& ename) {
  this->ename = ename;
}

std::string Props::getDept() {
  return dept;
}

void Props::setDept(const std::string& dept) {
  this->dept = dept;
}

std::string Props::toString() {
  std::string sb = "";
  sb += "{";
  sb += "\"empno\" : ";
  sb += "\"" + empno + "\"";
  sb += ",";
  sb += "\"salary\" : ";
  sb += "\"" + salary + "\"";
  sb += ",";
  sb += "\"ename\" : ";
  sb += "\"" + ename + "\"";
  sb += ",";
  sb += "\"dept\" : ";
  sb += "\"" + dept + "\"";
  sb += ",";
  sb.pop_back();
  sb += "}";
  return sb;
}

void Props::fromJson(boost::property_tree::ptree& json) {
  if(json.find("empno") != json.not_found()) {
    std::string empno_ = json.get<std::string>("empno");
    setEmpno(empno_);
  }
  if(json.find("salary") != json.not_found()) {
    std::string salary_ = json.get<std::string>("salary");
    setSalary(salary_);
  }
  if(json.find("ename") != json.not_found()) {
    std::string ename_ = json.get<std::string>("ename");
    setEname(ename_);
  }
  if(json.find("dept") != json.not_found()) {
    std::string dept_ = json.get<std::string>("dept");
    setDept(dept_);
  }
}

} /* namespace test */
} /* namespace examples */

