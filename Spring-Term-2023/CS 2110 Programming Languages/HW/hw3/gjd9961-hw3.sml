(*Problem 4.1*)
fun test1 a b = a::b;

(*Problem 4.2*)
fun test2 a [b] = a::[];

(*Problem 4.3*)
fun test3 g [] b  = b
  | test3 g (z::zs) b = test3 g zs (g(z,b))  ;

(*Problem 4.4*)
fun test4 g [a] b = b
  | test4 g (b::bs) c = test4 g (g(b,c)) bs;

(*Problem 4.5 fn : ('a,'a) tree -> ('a -> 'b) -> ('b -> 'a -> 'b) -> ('a,'b) tree*)
datatype ('a,'b) tree = Leaf of 'a
| Node of 'a * 'b;

(*Problem 5.1*)

exception NoItem;

fun get_index nil index = raise NoItem 
  | get_index (x::xs) index = 
if index = 0 then x
else get_index xs (index-1);

val test_get_index = get_index [1,2,3] 1;

(*Problem 5.2*)

fun listsum x total = 
let fun listsum_h [] = 0
  | listsum_h (x::xs) = x + listsum_h(xs)
  fun equals(a,b) = a = b
in equals(listsum_h x, total) end;

val test_listsum = listsum [1,2,3] 6;

(*Problem 5.3*)
exception Mismatch;

fun zip ([], _) =  []
  | zip (_, []) =  []
  | zip (b::bs, c::cs) = 
let fun len [] = 0
  | len (b::bs) = 1 + len(bs); in 
  if len(bs) = len(cs) then (b, c) :: zip(bs,cs) else raise Mismatch end;

val test_zip = zip([1,2,3], ["abc","a","b"]);

(*Problem 5.4*)

fun unzip [] = ([], [])
  | unzip ((b, c)::tuples) = 
        let val (bs, cs) = unzip tuples
        in (b::bs, c::cs) end;

val test_unzip = unzip test_zip;

(*Problem 5.5*)

fun bind (SOME a) (NONE) f = NONE 
  | bind (NONE) (SOME b) f = NONE
  | bind NONE NONE f = NONE
  | bind (SOME a) (SOME b) f =  SOME(f a b);

fun add x y = x+y;
val test_bind1 = bind (SOME 10) (SOME 3) add;
val test_bind2 = bind (SOME 10) NONE add;

(*Problem 5.6*)
fun getitem num (x::xs) = 
if num = 1 then SOME x else getitem (num-1) (xs)
  | getitem num [] = NONE;

val test_getitem1 = getitem 2 [1,2,3,4];
val test_getitem2 = getitem 5 [1,2,3,4];

(*Problem 5.7*)

fun lookup [] (str:string) = NONE
  | lookup ((x:string,y:int)::xs) (str:string) = 
if str = x then SOME y else lookup xs str;

val lookup_test1 = lookup [("hello",1), ("world", 2)] "hello";
val lookup_test2 = lookup [("hello",1), ("world", 2)] "world";
val lookup_test3 = lookup [("hello",1), ("world", 2)] "he";


signature MLQUEUE =
sig
  type 'a mlqueue
  exception Empty
  exception LevelNoExist
  val empty : unit -> 'a mlqueue
  val isEmpty : 'a mlqueue -> bool
  val enqueue : 'a mlqueue -> int -> int -> 'a -> 'a mlqueue
  val dequeue : 'a mlqueue -> 'a * 'a mlqueue
  val lookup : 'a mlqueue -> int -> (int * 'a) list
  val flatten : 'a mlqueue -> 'a list;
end;

structure MLQueue :> MLQUEUE =
struct
exception LevelNoExist
exception Empty
exception NotFound

type 'a mlqueue = (int * int * 'a) list;
  
fun empty unit = [];
  
fun isEmpty q = [] = q;

(* adjust as needed *)
val maxlevel = 10 ;

fun enqueue q l p e =
  if l < 1 orelse l > maxlevel then raise LevelNoExist
  else let
    val new_elem = (l, p, e)
    fun insert_elem [] = [new_elem]
      | insert_elem (h::t) =
        if #1 h > l then new_elem::h::t
        else if #1 h = l andalso #2 h >= p then h::insert_elem t
        else h::insert_elem t
  in insert_elem q end;

fun dequeue q =
  let
    fun find_highest_level [] = raise Empty
      | find_highest_level [x] = (x, [])
      | find_highest_level ((l1, p1, e1) :: (l2, p2, e2) :: rest) =
          if l1 < l2 then
            let val (max, rest') = find_highest_level ((l2, p2, e2) :: rest)
            in (max, (l1, p1, e1) :: rest') end
          else
            let val (max, rest') = find_highest_level ((l1, p1, e1) :: rest)
            in (max, (l2, p2, e2) :: rest') end
    val ((l, p, e), rest) = find_highest_level q
  in (e, rest) end;

fun lookup q p =
  if p < 0 then raise LevelNoExist
  else
    let
      fun loop [] _ acc = acc
        | loop ((l, pr, x)::xs) n acc =
            if n > maxlevel then acc
            else if pr = p then loop xs n ((l, x)::acc)
            else loop xs n acc
      val revList = loop q 1 []
    in revList end;
  
fun move pred q =
  let
    fun move_helper [] _ = []
      | move_helper ((l, p, e)::t) cur_level =
        if cur_level = 1 then (l, p, e)::move_helper t cur_level
        else if pred e then (cur_level - 1, p, e)::move_helper t (cur_level - 1)
        else (l, p, e)::move_helper t cur_level
  in move_helper q maxlevel end;

fun flatten q = List.map (fn (_, _, e) => e) q;
end;