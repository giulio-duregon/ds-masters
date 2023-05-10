
/* Define valid characters */
valid_char(a).
valid_char(b).
valid_char(c).
valid_char(d).
valid_char(e).
valid_char(f).
valid_char(g).
valid_char(h).
valid_char(i).
valid_char(j).

/* HELPER FUNCTIONS START HERE */

/*
    Helper function to count the total amount of shared elements between two lists
*/
count_shared_elements(List1, List2, Count) :-
    findall(X, (member(X, List1), member(X, List2)), Shared),
    length(Shared, Count).


/*
    Helper function to count the total amount of shared elements between two lists
    as long as the elements occur at the same index.
*/
count_same_pos([], [], 0) :- !.
count_same_pos([X|Xs], [X|Ys], Count) :-
    count_same_pos(Xs, Ys, NewCount),
    Count is NewCount + 1,
    !.
count_same_pos([_|Xs], [_|Ys], Count) :-
    count_same_pos(Xs, Ys, Count),
    !.

/*
    Helper function to ensure that after we call find all we only return unique lists
*/
unique_lists([], []). 
unique_lists([X|Xs], UniqueLists) :-
    member(X, Xs), 
    unique_lists(Xs, UniqueLists).
unique_lists([X|Xs], [X|UniqueXs]) :-
    unique_lists(Xs, UniqueXs).
 

/*
    Helper predicates to assert logic as provided in the instruction lists.
    Asserts that the number of elements shared in the same position in each list
    follows what was set for by the examples.
*/

same_pos_a(List) :-
    count_same_pos(List, [i, j, f, b], Count),
    Count =:= 0,
    !.
same_pos_b(List) :-
    count_same_pos(List, [c, b, g, j], Count),
    Count =:= 1,
    !.
same_pos_c(List) :-
    count_same_pos(List, [d, g, j, e], Count),
    Count =:= 1,
    !.
same_pos_d(List) :-
    count_same_pos(List, [e, h, c, b], Count),
    Count =:= 1,
    !.

same_pos_e(List) :-
    count_same_pos(List, [b, c, d, h], Count),
    Count =:= 0,
    !.

/*
    Helper predicates that ensure the number of common elements
    between two lists matches what the instructions specified.
*/
shares_a(I) :- count_shared_elements(I, [i, j, f, b],2).
shares_b(I) :- count_shared_elements(I, [c, b, g, j],2).
shares_c(I) :- count_shared_elements(I, [d, g, j, e],2).
shares_d(I) :- count_shared_elements(I, [e, h, c, b],2).
shares_e(I) :- count_shared_elements(I, [b, c, d, h],3).


/*  
    Helper function that checks for all similarity rules.
    Note that in this implementation, count_shared_elements
    Corresponds to #D + #S as S elements imply shared but same
    position, while D elements imply shared.
*/
check_list_compatability(I) :- 
shares_a(I),
shares_b(I),
shares_c(I),
shares_d(I),
shares_e(I),
same_pos_a(I),
same_pos_b(I),
same_pos_c(I),
same_pos_d(I),
same_pos_e(I).

/*  
    Helper function that does the majority of the logic
    Tests for length, valid characters, and that all the constraints 
    per the guidelines are met.
*/
list_checker([A,B,C,D]) :- 
length([A, B, C, D], 4), 
valid_char(A), 
valid_char(B), 
valid_char(C), 
valid_char(D),
check_list_compatability([A,B,C,D]).


/*Implementation */
solution(Result) :- findall(O, list_checker(O), Answers), unique_lists(Answers, Result).


