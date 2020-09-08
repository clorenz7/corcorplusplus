# corcorplusplus
Learning / Practicing C++

## Language Notes

### Pointers and Dereferencing

& is an address operator
- This is distinct from reference when applied to types

`*` is a dereference operator

```c++
// Pointer creation: space is irrelevant: ptr is a pointer, q is an int
int *ptr, q; //same as int* ptr, q;

// Reference creation:
vector<int> homework;
vector<int>& hw = homework; // hw is a synonym for homework. 

// The following means pass a reference of hw (others are copied)
int grade(int midterm, int final, vector<int>& hwork) { }

// Address operation:
int x = 5;
int* p = &x; // p points to the address of x
*p= 6;
return (x == 6) // will return true
```
