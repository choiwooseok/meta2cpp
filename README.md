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
./bin/codeGen -i ../meta/emp.json -o ../generated/
```

# Exmaples
```
// INPUT META
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
# OUTPUTS
* See test/src/generated/
