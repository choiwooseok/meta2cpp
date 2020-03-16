#ifndef EMP_H_
#define EMP_H_

#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace test {
namespace examples {

class Emp {
public:
    Emp() = default;
    Emp(const Emp&) = default;
    Emp(Emp&&) = default;
    Emp& operator=(const Emp&) = default;
    Emp& operator=(Emp&&) = default;
    virtual ~Emp() = default;

private:
    /**
    * fieldName : empno
    * fieldDesc : 사번
    */
    int empno;

public:
    int getEmpno();
    void setEmpno(int empno);

private:
    /**
    * fieldName : salary
    * fieldDesc : 임금
    */
    unsigned long salary;

public:
    unsigned long getSalary();
    void setSalary(unsigned long salary);

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
    std::vector< std::string > dept;

public:
    std::vector< std::string >& getDept();
    void setDept(const std::vector< std::string >& dept);
public:
    virtual std::string toString();
    void fromJson(boost::property_tree::ptree& json);
};
} /* namespace test */
} /* namespace examples */

#endif /* EMP_H_ */
