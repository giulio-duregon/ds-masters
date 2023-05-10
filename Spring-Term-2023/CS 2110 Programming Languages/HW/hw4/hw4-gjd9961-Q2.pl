/*Helper functions*/
my_delete([], _, []).
my_delete([X|T], X, R) :- my_delete(T, X, R).
my_delete([H|T], X, [H|R]) :- H \= X, my_delete(T, X, R).


is_list([]).
is_list([_|T]) :- is_list(T).

my_length([], 0).
my_length([_|T], N) :- my_length(T, N1), N is N1 + 1.

encode_helper([X,X|T], N, R) :- encode_helper([X|T], N1, R), N is N1 + 1.
encode_helper([_], 1, []).
encode_helper([], 0, []).
encode_helper([X,Y|T], 1, [Y|T]) :- X \= Y.
encode_helper([X,X|T], N, R) :- encode_helper([X|T], N1, R), N is N1 + 1.

/*2.1 Remove Items - Uses Helper function my delete*/
remove_items(_,[],[]).
remove_items([], L, L).
remove_items([H|T], L, O) :- my_delete(L, H, NewL), remove_items(T, NewL, O).

/*2.2 My Flatten - Uses helper function is list*/
my_flatten([], []).
my_flatten(X, [X]) :- \+ is_list(X).
my_flatten([H|T], L) :- my_flatten(H, FH), my_flatten(T, FT), append(FH, FT, L).

/*2.3 Compress*/
compress([], []).
compress([X], [X]).
compress([X,X|T], L) :- compress([X|T], L).
compress([X,Y|T], [X|L]) :- X \= Y, compress([Y|T], L).


/*2.4 Encode*/
encode([], []).
encode([X], [[1,X]]).
encode([X,X|T], [[N,X]|L]) :- encode([X|T], [[N1,X]|L]), N is N1 + 1.
encode([X,Y|T], [[1,X]|L]) :- X \= Y, encode([Y|T], L).

/*2.5 Encode Modified*/
encode_modified([], []).
encode_modified([X], [X]).
encode_modified([X,X|T], [[N,X]|T2]) :- encode_helper([X,X|T], N, R), encode_modified(R, T2).
encode_modified([H|T], [H|T2]) :- \+ T = [], encode_modified(T, T2).

/*2.6 Rotate */
rotate(L, N, R) :-
    my_length(L, Len),
    N1 is (N mod Len + Len) mod Len,
    append(Start, End, L),
    my_length(Start, N1),
    append(End, Start, R).


