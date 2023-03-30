# CS 2210 - Programming Languages - Giulio Duregon - gjd9961

## Q1: Language Standards

### 1-1)

When a variable is declared final in Java, it can be assigned a value just once (when it is unassigned). To make a variable final, one needs to use the final keyword. However, there are variables which are implicitly final. What are the different kind of these variables?

- From page 99 of the 15th edition of the java language standard in section 4.12.4 it states that three different kinds of variables are implicitly final:  1. a field of an interface 2. a local variable declared as a resource of a try-with-resources statement and 3. an exception parameter of a multi-catch clause. My interpretation is that variables used in error handling tend to be implicitly final, as well as those defined in high level abstract interfaces, designed to be shared amongst disparate classes that may implment said interface.

### 1-2)

As far as floating pointing calculations in Java are concerned, the JVM implementation is free to use extra precision where available thus giving different precision across different platforms. In order to prevent this behavior, Java allows the use of a modifier keyword. What is the this keyword? Give an example usage of this modifier.

- From page 508 section 15.4 `FP-Strict Expressions` : The keyword is `strictfp` and is used when you want to control what type of precision a floating point number gets when the JVM has freedom to choose (and upgrade to extra precision). In section 8.1.1.3, 8.4.3.5, and 9.1.1.2 shows how to use the `strictfp` keyword on java classes, methods, and interfaces. Here is an example of the usage of the modifier on an interfaces instance variables and methods:

```java

// Toy student interface using strictfp modifier keyword
strictfp Interface Student 
{
    // toy private strictfp variable and 
    private double gpa;
    public double getGPA() // Implicitly strictfp as the interface is defined as such
    {
        return gpa;
    }
}
```

### 1-3)

In C++, we can change the contents of a string variable (i.e., string is mutable). Is the same allowed in Java? If yes, give an example. If no, what is an alternative to string data type which can be used for this purpose? Cite the specific section in Java Language Specification.

- From section 4.3.3, page 67,  ***The String class***, `String` variables are immutible, and thus have a constant value. When a string is modified, a new `String` object is created and referenced instead. On page 374, section 10.9 "An Array of Characters is Not a `String`", the Java Language Specifications suggests using an array of `char`, which indeed has mutable elements (though not null-character terminated as is done in C++).

### 1-4)

We know that, generally, variables in an outer scope can be hidden by variables in an inner scope. What about class and instance variables in Java? Can those be hidden? Cite the location(s) in JLS 15 where this question is answered.

- Many sections in Chapter 8 - `Classes` of the Java Langugage specifications highlight different ways to hide variables initialized in classes. One obvious example is labeling instance or class variables as `private` or `protected`, which limits direct access to these variables to only the instance which holds the variables (private) or initialized within the same package (protected). There is also a more convulted way to hide class variables as described in Example 8.3.1.1-2, page 247. This way involves using a base class that initializes a static variable, then creating a derived class that extends the base, with a public static method that uses a `super` modifier keyword to access the base classes class and or instance variable. More discussion on other ways to "shadow" or "obscure" class and instance variables is given in sections 6.4 `Shadowing and Obscuring`.

### 1-5)

In C++, a common way to access objects created on the heap is using pointers. However, use of pointers sometimes creates memory management issues when programmers have many pointers pointing to the same object. This can result in the creation of zombie pointers. In an effort to mitigate this issue, the concept of smart pointers was introduced in C++. Two of the most commonly used smart pointers are unique ptr and shared ptr. What is the difference between these two? When should one be used over the other?

- In the C++ Working Draft Language Specifications, page 609 section 23.11.1 describes the two main `smartptr` objects: `unique_ptr` and `shared_ptr`. A `unique_ptr` object is described as an object that owns a reference to another object which is managed through a pointer variable. The `unique_ptr` object is tasked with deleting its "owned" object and pointer when it itself is deleted, thus avoiding zomie objects on the heap and zombie pointers not pointing at live data. A `unique_ptr` object can transfer ownership of its object and associated pointer to another `unique_ptr` object through class method function calls. A `shared_ptr` on the other hand, stores a pointer, which can be stored amongst other shared_ptr objects, however, the last remaining `shared_ptr` object pointing to an object on the heap is designated and responsible for destorying to object and freeing the heap memory upon its deletion. Both are different ways when dealing with pointer variables and objects on the heap to delete / tear down objects responsibiliy for effective memory management. The main differences between the two are only a single `unique_ptr` object can hold a pointer to a specific object, while many `shared_ptr` objects can hold the same pointer to the same object. While `unique_ptr` is solely tasked with object tear down, there is a last-man standing approach for `shared_ptr`.

### 1-6)

When an exception is thrown in C++, all the existing objects within the scope need to be destroyed. What is this object destruction process called? Explain how objects are destroyed in this process. Hint: Read about constructors and destructors in the C++ language standard document.

- In section 18.2: Constructors and destructors - page 427 of the C++ Language specifications, the tear-down process of objects within the current scope during an exception is called `stack unwinding`. During `stack unwinding` a destructor call is made to each automatic object created since the try block was entered. Objects are destroyed in reverse order from the execution of instructions. Destructors of class sub-objects are also called during this process, again destroyed in reverse order of the completion of their construction. This ensures that all memory used during the try block is freed up to avoid memory leaks.

### 1.7)

In C++, one may have two distinct entities with the same name, in the same scope, such that one name hides the other. How is that possible? (Normally, name hiding only occurs when the names are in different inner and outer scopes.) What does section 6.3.10 of the C++ standard have to say about this?

- In section 6.3.10 of the C++ langugage standard, page 50, name hiding within scopes is discussed. There are a few situations where this can occur, one clear example is the `using-directive` i.e.

```c++
using namespace std;
string name; // Uses std::string
while (true)
{
    // hides declerations with the same namespace of std
    using namespace example; 
    string second_name; //uses example::string (if it exists)
}
```

- Other than `using-directives` there are a few other ways to hide names, primarily involving classes and enumerations. If another variable, data member, function, or enumeration is declared in the same scope, (with the same name of course), then the previously defined class or enumeration name is hidden and the more recently defined one is visible. Note: if a name is in a scope and it is not hidden it is said to bew visible.

### 1-8)

What does it mean in C++ when an identifier is visible? What does it mean in C when an identifier is visible?

- In C++ if a name is in a scope and it is not hidden it is said to be visible (section 6.3.10 of the C++ langugage standard, page 50). In C, an identifier is said to be visible if it can be used, therefore, if an identifier declared in an outer scope is hidden due to a identifier by the same name declared in an inner scope, the outer identifier is `hidden`, not `visible`, and cannot be used (source, page 28 section `6.2.1 Scopes and Identifiers`, C Langugage Standard.)

### 1-9)

In C++, the most common type of inheritance in an object-oriented program is public inheritance, denoted by the notation:
```class A : public B  {...}``` Here, B is the base class and A is the subclass. Public inheritance means that public members of class B are accessible as public members of class A and protected members of class B are accessible as protected members of class A.
However there is also protected inheritance. For this we write:
```class A : protected B  {...}```
According to the C++ standard, what does this mean?

- From the C++ language standard, page 271, section `14.2: Accessibility of base classes and base class members`: protected inheretence means that in the derived class, the public and the protected memebers of the base class are accessible as `protected` members of the derived class.

### 1-10)

C# has a special control structure called a foreach loop which, interestingly enough, was the inspiration for one of C++’s two for loop variations. Unlike the more traditional for loop in which the programmer can iterate over any condition they choose, the foreach loop imposes several restrictions on what the loop can do. Explain two ways in which foreach is different from the more general for loop.

- In section `13.9.5: The foreach statement`, page 232 of the C# language standard, the `foreach` statement is defined. The statement enumerates elements of a collection, and then executes an embedded statement for each element in the collection. The two main differences are that unlike the traditional for loop, a programmer is forced to iterate over the items in a collection explicitly. The items during iteration are read-only, and no specification is given for how long to loop for (i.e. you couldn't explicitly instruct the foreach statement to loop over the first half of the elements in an array.) The order of iteration is also not something that you can customize (as far as I can tell).

## Q2: Grammars and Parse Trees

### 2-1)

- a) This language describes "postfix notation" or "reverse polish notation", where all strings are comprised of sequences of one or more a's and/or b's, followed by a mathematical operator character, a "+" or "-" character i.e. `ab+ba-` and `aab-+ba-`
- b) This is a language that describes strings that are either 1) empty 2) strings comprised of any amount of the character "b" and nothing else 3) an number "n" of the character "a", followed by any number of "b"s (0 included), followed by 2n number of "a"s, i.e. `abaa` or `aabbbbbbbaaaa`. The number of "a" characteres present in the string would always be a multiple of 3, (0 included). In psuedo-regex code i would describe the language as $(a)^nb^*(a)^{2n}$
- c) This is a language that describes all strings with one or more "a" characters and any amount of "b" characters in any order. i.e. in psuedo-code regex it would be $[ab]^*a^+[ab]^*$
- d) This language describes strings that can either be null, a single character ("a" or "b"), or many characters, however if it is a many character string then it can be filled with any number of "a"s and "b"s, but the starting and ending character must match i.e. `abbba` or `bbbbb` or `aabaa`.
- e) This language describes any string that is either empty or formed by the characters "[" and "]" such that all open brackets (a "[" character not yet follow by a "]" character) are eventually "closed" (followed by a "]" character), and all "nested" open brackets ("[" characters following a "[" character)) get "closed" sequentially" (i.e. after $n$ "open" brackets, if a closing bracket "]" is encountered, there must be $n$ of them). Valid strings could be: the empty string,`[[[]]][[]]`, `[]`,`[[]]`

### 2-2)

- a) Image:
- b) The new grammar is the same as the given except fore the addition of another non-terminal symbol: B: $N=\{S,A,B\}$. The grammar is as follows:
$$
\begin{split}
    S &\rightarrow A\ S \ | \  \epsilon \\
    A &\rightarrow B\ 1\  | \ \epsilon \\
    B &\rightarrow 0 \ B \ 1 \ | \ \epsilon
\end{split}
$$
- c) Image:

### 2-3)

Here our new grammar G3 defines a new language $L3$ which is the union between the first two languages, $L1$ and $L2$. We can express this formally like so:
$$
    \begin{equation}
    \begin{split}
    G3 &= \{\Sigma, N3, S3, \delta3\} \\
    &= \{\Sigma, N1\cup N2\cup \{S3\}, S3, \delta3\} \textit{ as } S3\notin N1\cup N2 \\
    &= \{\Sigma, N1\cup N2\cup \{S3\}, S3, \delta1\cup \delta2 \cup \{S3\rightarrow S1, S3\rightarrow S2\}\} \\
    &= \{\Sigma, N1\cup N2\cup \{S3\}, S3, \delta1\cup \delta2 \cup \{S3\rightarrow S1 | S2 \}\} \\
    \end{split}
    \end{equation}
$$

- As our grammar contains our new distinguished non terminal symbol, $S3 \in N3$, and $S3$ maps to either $S1$ or $S2$, which produce distinct, non-overllaping $(N1\cap N2 = \{\empty\})$ parse trees, all start symbols $S3$ will result in productions of either $G1$ or $G2$, using only symbols from $L1$ or $L2$ respectively.

### 2-4)

Assuming starting symbol $S$, terminal symbols $\{a,b\}$ and non-terminal symbols $N=\{S,A,B\}$, with normal definitions for the rules/productions $|, \rightarrow, \epsilon$

- a) $$S\rightarrow aSaa \ | B | \epsilon $$
    $$B \rightarrow b\ B \ | \ \epsilon $$
- b) $$S\rightarrow a \  A \ a \ | \ b \ A \ b \ | \ a \ |\ b$$
$$A \rightarrow a\ A \ | \ b\ A$$
- c) $$S\rightarrow a\ A \ | A\ S\  | \ S\ B\ A$$
$$A \rightarrow Aa \ | \ \epsilon  $$
$$B \rightarrow B\ B \ | \ a\ B\ b\  | \ b\ B\ a \ | \ \epsilon$$
- d) $$S\rightarrow a\ S\ b \ |\  b\ S\ b \ | \ a \ | \ b \ | \ \epsilon$$

### 2-5)

- a) A top down parser would struggle with this grammar as in two of the lines, the root symbol and the X symbol, the first symbol on the right hand side is the same as the left hand side. This left-recursive structure of the grammar can give top-down parsers problems, as when they analyze the next token if S is on top of stack and an X on the input are present the parser won't be able to predict the next token. Normally left recursion is easy to eliminate, by modifying the grammar mechanically one approach being changing from left recursion to right recursion.
- b) In changing the grammar from left recursive, we introduce new symbols to our grammar: $\Sigma = \{A,B,C, S,X,Y\}$:
$$
\begin{split}
S &\rightarrow XA\\
A &\rightarrow +XA | \epsilon \\
X &\rightarrow YB\\
B &\rightarrow *\ Y\ B\  |\  \epsilon \\
Y &\rightarrow a \\
\end{split}
$$

## Q3: Regular Expressions

### 3-1)

- a) Write a regular expression recognizing strings over the alphabet {a, b, c} which contain exactly one ‘a’ along with any number of b’s and c’s.

- Regex: $$[bc]^*a[bc]^*$$ where [bc] means b|c
- b) Write a regular expression recognizing strings over the alphabet {a, b, c} where all occurrences of ‘a’ appear in groups of three. (Please keep in mind that zero is a multiple of three).
- Regex: $$[bc]^*(aaa)^*[bc]^*$$
- c) Write a regular expression recognizing strings over the alphabet {a,b,c} whose length is a multiple of 5 (Please keep in mind that zero is a multiple of 5).
- Here we take advantage of our alphabet, which we call $\Sigma$, and the period operator "." (used to describe $\alpha$, any character in our alphabet). I.e. we have $$. \equiv \{\alpha | \alpha \in \Sigma\}, \Sigma=\{a,b,c\}$$ My making a group of 5 characters, i.e.: $$(.....)^*$$ we can get any 5 characters in our alphabet, 0 or more times. I'm not sure if "captured grouping" was mentioned in lecture 1 (i switched into the class the second week and don't see anything about it in the slides), but if so, you can make the expression an atomic group by adding the symbols ?> at the beggining like so: $(?>.....)^*$
- d) Write a regular expression recognizing even integers.
- This is fairly simple: the leftmost digit can be any digit other than 0, (this is optional), the middle optional digit can be any number, and the rightmost number must be an even digit: $[1-9]^*[0-9]^*[0|2|4|6|8]$
- e) Write a regular expression recognizing all strings of 0’s and 1’s not containing the substring 101.
- I couldn't find a good way to do this without a "lookahead" or forward reference feature. The best I could come up with without a lookahead was: $0^*1^*000^*1^*$ or $0^*1^*0\{2,\}0^*1^*$   (where 0{2,} defines the occurance of "0" 2 or more times)

### 3-2)

$R^*$ is defined as 0 or more occurances i.e. $R^*=R^+ | \ R \ |\ \epsilon = R^+|R^?$ , where $R^+$ is 1 or more occurances, i.e. $R^+= R^*R = RR^*$. We have:
$$
\begin{equation}
\begin{split}
R^*&= R^+|R|\epsilon \\
&= R^*R | R | \epsilon \\
&= (R^*R|R)^*
\end{split}
\end{equation}
$$

## Q5: Associativity and Precedence

1. $$ 5\times 2 -6 + 7 / 7 \rightarrow 5 \times ((2-(6+7))/7) = -45/7$$
2. $$ 8 \times 8 / 4 + 4 / 2 \times 2 \rightarrow 8\times(8 / ((4+4)/(2*2)) = 24$$
3. $$5-3 \times 5 \% 3 +2 \rightarrow (5-3) \times (5 \%(3+2))  = 2 \times 0 = 0$$
4. $$ 10 -2 +6 \times 10 - 2 / 6 + 4 \rightarrow (10-(2+6)) \times ((10-2)/(6+4)) = 1.6$$
5. $$ 2 + 5 / 2 \times 5 - 4 \% 2 \rightarrow (2+5)/(2\times((5-4)\%2)) = 7/2$$
6. $$12-4 \times 9 - 4 / 10 / 6 = (12-4)\times((9-4)/(10/6)) = 24 $$

## Q6: Short-Circuit Evaluation

### 6-1)

Desired Output: “Hello There World! Hello Darling!” assuming short-circuit evaluation

```c++
if ( f() && h() && i() || g() || f() && i() )
  {
    cout << "What lovely weather!" << endl;
  }
bool f() {
    cout << "Hello ";
    return true;
  }
bool g() {
    cout << "World! ";
    return false;
  }
bool h() {
    cout << "There ";
    return false;
  }
bool i() {
    cout << "Darling! " << endl;
    // This is either if you don't mind the 
    // extra "What lovely weather!" the follows
    // after Hello There World! Hello Darling!
    // If you do mind, then it must be set to false
    return either; 
  }
```

### 6-2)

Per the C++ Language Standard, section `8.14: Logical AND operator`, page 135, left-to-right short circuit evaluation is a feature of the language, and I imagine as such compilers are required to perform short-circuit evaluation. This holds true for the logical OR operator, `||` , as well.

### 6-3)

In my opinion, short-circuit evaluation is a good feature of a language. In all cases, if a logical OR is being used, then time is saved, as additional funciton calls or logical checks are avoided. In some situations, outlined in the function `main()` below, short-circuit evaluation can eliminate time and waste during a logical AND operation. For instance, if the function `b()` performs complicated and computationally intensive logical checks to evaluate to true or false, then avoiding it all together with short circuit evaluation is desirable. Especially if state is changed our output is generated during later stages of conditional evaluation, as seen in problem 1, the functionality of a program can change signifcantly when using short-circuit evaluation, and thus logical conditions should be considered by the programmer carefully.

```c++
bool a(){
    // some easy math check
    return true;
}
int some_condition(){
    // Returns 
    int rand = std::rand()% 2;
    return rand;
}
bool b(){
    // very computationally expensive logic implemented here
    if (some_condition()){

        std::cout << "We're doing lots of intense operations" << std::endl;
        return false;
    }
    return true
}
int main(){
    // Short circuit here -- This is good and saves us time
    if (a() || b()){
        std::cout << "We're in the if" << std::endl;
    }

    // Short circuit evaluation doesn't save us much time here
    if (a() && b()){
        // Some logic...
    }

    // Again, short circuit evaluation saves us time here. 
    // If c() returns false we don't need to evaluate b()
    if (a() && c() && b()){

    }
    return 0;
}

```

## Q7: Bindings and Nested Subprograms

Assuming static scoping:

| Unit | Var | Where Declared |
| :----| :---: | ---: |
main | a | main |
main | b | main |
sub1 | a | sub1|
sub1 | b | main|
sub2 | a | sub2|
sub2 | b | main|
sub2 | c | sub2|
sub3 | a | sub2|
sub3 | b | sub3|
sub3 | c | sub2|
sub3 | d | sub3|
