#include "Emp.h"

namespace test {
namespace examples {

int Emp::getEmpno() {
    return empno;
}

void Emp::setEmpno(int empno) {
    this->empno = empno;
}

unsigned long Emp::getSalary() {
    return salary;
}

void Emp::setSalary(unsigned long salary) {
    this->salary = salary;
}

std::string Emp::getEname() {
    return ename;
}

void Emp::setEname(const std::string& ename) {
    this->ename = ename;
}

std::vector< std::string >& Emp::getDept() {
    return dept;
}

void Emp::setDept(const std::vector< std::string >& dept) {
    this->dept = dept;
}

std::string Emp::toString() {
    std::string sb = "";
    sb += "empno : ";
    sb += std::to_string(empno);
    sb += ",";
    sb += "salary : ";
    sb += std::to_string(salary);
    sb += ",";
    sb += "ename : ";
    sb += ename;
    sb += ",";
    sb += "dept : ";
    sb += "[";
    for(auto elem : dept) {
        sb += elem;
        sb += ",";
    }
    sb.pop_back();
    sb += "]";
    sb += ",";
    sb.pop_back();
    return sb;
}

} /* namespace test */
} /* namespace examples */

