[![CodeFactor](https://www.codefactor.io/repository/github/choiwooseok/meta2cpp/badge)](https://www.codefactor.io/repository/github/choiwooseok/meta2cpp)

# meta2cpp
* meta to cpp Class Generator proj
    * generate class with methods
    * fromJson
    * toString
    * getter/setter
    
# Prerequisite
* conan - for boost

# Build
```
mkdir build && cd build
conan install ..
cmake ..
make
```

# Usage
```
./bin/codeGen -i ../meta/emp.json -o ../test/src/generated/
```

# Exmaples
# INPUT
```
{
    "class-name" : "Emp",
    "parent-class-name" : "",
    "namespaces" : ["test", "examples"],

    "includes" : [
        "string",
        "vector"
    ],

    "fields" : [
        {
            "fieldName" : "empno",
            "fieldType" : "int",
            "isArray" : false,
            "description" : "사번"
        },
        {
            "fieldName" : "salary",
            "fieldType" : "unsigned long",
            "isArray" : false,
            "description" : "임금"
        },
        {
            "fieldName" : "ename",
            "fieldType" : "string",
            "isArray" : false,
            "description" : "이름"
        },
        {
            "fieldName" : "dept",
            "fieldType" : "string",
            "isArray" : true,
            "description" : "부서"
        }
    ]
}

```
# OUTPUT
* See test/src/generated/

# Support fieldType
* isArray : true -> vector< fieldType > will be generated
```
    std::unordered_map<std::string, std::string> cppTypes = {
        {"bool", "bool"},
        {"char", "char"},
        {"unsigned char", "unsigned char"},
        {"short", "short"},
        {"unsigned short", "unsigned short"},
        {"int", "int"},
        {"unsigned int", "unsigned int"},
        {"double", "double"},
        {"float", "float"},
        {"long", "long"},
        {"unsigned long", "unsigned long"},
        {"string", "std::string"}
    };
```
