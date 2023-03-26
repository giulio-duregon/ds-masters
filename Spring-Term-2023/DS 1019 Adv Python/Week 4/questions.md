# Pass by name questions

```python
## Python syntax but assuming pass by name
a = 1
def example(a, b, c):
    
    for i in range(2):
        print(a,b,c)
        a += 1

>>> example(a, a/2, a/4)
>>> output:
1 .5 .25
2 1 .5
```

Straight forward because we pass a as an actual parameter, and modify it in the body of the procedure

```python
## Python syntax but assuming pass by name
example_input = 1
def example(a, b, c):
    
    for i in range(2):
        print(a,b,c)
        a += 1

>>> example(example_input, example_input/2, example_input/4)
>>> output:
### Same behavior?
1 .5 .25
2 1 .5
```

If the actual parameter passed to the formal parameter has a different name, does pass by name behave the same? I.E. is a reference of example input passed to the function, and when its alias `a` gets modified, so does the value of `example_input`

i.e. what happens if after the function call we do:

```python
 print(example_input) 
```

# Lambda Calculus Questions

Order of operations:

- Appplication (left-associative), then abstraction (right-associative)

Questions:

- How should I think about this? Application `MM` confuses me, due to the recursive nature of the parse tree with the symbol `M`.
- For instance, when I do math and evaluate an expression like: $1 + 2 *3$  I go from left to right, first passing over the input looking for division or multiplication symbols. Once I find one I group the two values together i.e. $1 + (2*3)$, then repeat the same procedure again but this time for addition / subtraction etc.
- I'm struggling to create an analog for lambda calculus.
- How to differentiate between parameters being passed vs extended body of a function, i.e. $$\lambda x.xyz =? (\lambda x.xy)(z)=? (\lambda x.(xyz))$$

Lambda Calculus Examples

$$ \lambda x.y \ \lambda x.z $$



$$
1-~ ((\lambda x.x) (\lambda xz.yzz))((\lambda y.yy)(\lambda x.xz))
$$

$$2-~ (\lambda xz.zz)((\lambda y.y)(\lambda(x.xz)))$$
$$3-~ (\lambda xz.zz)(\lambda(x.xz))$$