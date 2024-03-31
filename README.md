# hillisp

[CUDA](https://en.wikipedia.org/wiki/CUDA) parallel lisp inspired by
[Connection
Machines](https://en.wikipedia.org/wiki/Connection_Machine).

Inspiration for Hillisp comes from the book [The Connection Machine
](http://www.amazon.com/The-Connection-Machine-Artificial-Intelligence/dp/0262580977)
by [Daniel Hillis](https://en.wikipedia.org/wiki/Danny_Hillis) and the
paper [Connection Machine Lisp: fine-grained parallel symbolic
processing](http://dl.acm.org/citation.cfm?id=319870) by Hillis and
[Guy L. Steele, Jr.](https://en.wikipedia.org/wiki/Guy_L._Steele,_Jr.)

All parallelism in hillisp is organized around a data structure called
a *xapping* (rhymes with "mapping").  A xapping is something like an
array and something like a hash table but all the entires in a xapping
can be operated on in parallel, for example to perform associative
searching. This data structure by itself is not a particularly
original idea; the innovation in hillisp lies in the program notation
used in conjunction with it.

To be precite, a xapping is an unordered set of ordered pairs.  The
first item of each pale is called an *index*, and the second item is
called a *value*. We write a pair we write a pair as *index:value*. An
index or value may be any Lisp object. A xapping cannot contain two
distinct pairs whose indices are the same; all the indices in a
xapping are distinct (but the values need not be distinct). There is a
question of what is meant by "same"; for now assume that a hillisp
function `eql` determines sameness.  Here is an example of a xapping
that maps symbols to other symbols:

{sky:blue apple:red grass:green}

The same xapping could have been written in this manner:

{apple:red sky:blue grass:green}

The order in which the pair, are written makes no difference.

To speak in terms of implementation on a parallel computer, one may
think of an index as a label for a processor, and think of the
corresponding value as being stored in the local memory of that
processor. The index might or might not be stored explicitly also.

The xapping shown above might be represented, for example, by storing
pointers to the symbols `apple` and `red` in proceseor A, `sky` and
`blue` in processor B, and `grass` and `green` in processor C.

The ingenious reader can no doubt invent many other representations
for xappings suitable for particular purposes. In any case, it is well
to think of indices as labelling abstract processors, and to think of
two values in two xappings, as being stored in the same processor if
they have the same index, Semantically a xapping really is like an
array or hash table, where the indices may be any Hillisp objects.

A xapping may be accessed by index to obtain a value:

? (xref '{sky:blue apple:red grass:green} 'apple) ; => red

Sometimes the index and the value of a pair are the same (that is,
`eql`). As a convenient abbreviation, each a pair may be written
within xapping-notation as just the value, without the index or the
colon. For example,

? {apple:fruit color:abstraction abstraction:abstraction}
{apple:fruit color:abstraction abstraction}

This is most convenient in the case where all the pairs may be so
abbreviated:

{red green blue}

means the same as:

{red:red green:green blue:blue}

but is considerably shorter. If all the elements of a xapping can be
abbreviated in this manner, then the xapping is called a `xet` (rhymes
with "set").

If a finite xapping has a set of indices that are consecutive
nonnagative integers beginning with zero, then the xapping may be
abbreviated by writing the values in order according to their indices,
separated by whitespace and surrounded by brackets.  For example, the
notation `[red green blue]` is merely an abbreviation for `{0:red
1:green 2:blue}`. A xapping that can be abbreviated in this manner is
called a xector (rhymes with "vector'). The use of xectors in Hillisp
is similar to the use of vectors in APL.

{0:red 1:green 2:blue} ; [red green blue]

{:5}

{:}

{sqrt}

{pi:1.772453851 e:1.16487212 -1:i sqrt}




hillisp CUDA arrays are called "xectors" and can be operated on in
[CUDA
SIMT](https://en.wikipedia.org/wiki/Single_instruction,_multiple_threads)
fashion using a parallel lisp syntax.  Inspirations for this syntax
were described in [The Connection Machine (link to book on
Amazon)](http://www.amazon.com/The-Connection-Machine-Artificial-Intelligence/dp/0262580977)
by [Daniel Hillis](https://en.wikipedia.org/wiki/Danny_Hillis) and the
paper [Connection Machine Lisp: fine-grained parallel symbolic
processing](http://dl.acm.org/citation.cfm?id=319870) by Hillis and
[Guy L. Steele, Jr.](https://en.wikipedia.org/wiki/Guy_L._Steele,_Jr.)

## install

Just type 'make'.  You will need a GPU with compute capability of 3.0
or better and CUDA 7.0+ installed.  The interpreter is the 'lisp'
binary.  Install the 'rlwrap' program to get readline support with the
'hillisp' script.

## lisp

hillisp is an extremely tiny Lisp implementation written in CUDA C++.
Its primary purpose is to drive the GPU as efficiently as possible.
The language itself is not designed to be especially performant or
featureful, as any computational density your program needs should be
done in-kernel on the CUDA device and should be appropriate for CUDA
workloads.

To that end, the interpreter is very simple, has few "general purpose"
programming features, and is designed to undertake its interpretation
duties (ie, scheduling, garbage collection) asynchronously while the
GPU is running CUDA kernels.  In this way it attempts to be as "zero
time" as possible.

hillisp is not a general purpose programming language, but a language
for exploring parallel algorithms using the high-level language
developed for Connection Machines on extremely powerful, modern GPU
hardware.

## xectors

A xector is constructed using bracket syntax.  Currently only int64_t
and double xectors are supported.  Lisp functions operate on
traditional arguments like numbers, but can also operate on xectors
entirely in the GPU.  For example, the '*' function can multiply two
integers together (this is done on the CUDA "host", the CPU) or it can
multiply two xectors together (this is done on the CUDA "device", the
GPU):

    ? (* 3 4)  ; mulitply on host
    : 12

    ? (* [1 2 3] [4 5 6]) ; parallel mulitply on device
    : [4 10 18]

Large arrays can be created and intialized entirely on-device:

    ? (+ (fill 3 1000000) (fill 4 1000000))
    : [7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 ... 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7]
    ?

The 'fill' function takes a value and a size and creates a xector of
the specified size and fills it, in parallel, with that value.  Thus,
the second expression above creates two xectors of one million
integers each, fills them with the values 3 and 7, respectively, then
adds them together, yielding a xector containing one million "10"
values.

This is conceptually very similar to the following numpy code:

    >>> 3 + 4
    7
    >>> a = np.empty(1000000)
    >>> b = np.empty(1000000)
    >>> a.fill(3)
    >>> b.fill(4)
    >>> a + b
    array([ 7.,  7.,  7., ...,  7.,  7.,  7.])
    >>>

## CUDA kernels

Internally, '+' and 'fill' cause CUDA kernels to be queued for launch
asynchronously into a CUDA stream.  First two 'fill' kernels, then a
'+' kernel.  Since the 'fill' kernels don't depend on each other, they
can be dispatched in parallel.  While the first two kernels complete
the interpreter does garbage collection, and queues up the next kernel
to run, the '+' kernel which waits until the 'fill' kernels complete
before adding the two xectors together. This finally yields a third
xector containing the result of one million integers set to value '7'.

Xectors are allocated using CUDA [Unified
Memory](http://devblogs.nvidia.com/parallelforall/unified-memory-in-cuda-6/).
Pointers to xector data can be accessed by both the host and the
device.  CUDA manages the unified memory so that only the minimal
amount of copying to and from the device to the host is required.

## TODO

  - N-dimensional xectors.

  - Unicode strings.

  - Multi-device support.

  - Currently only 64 bit integer, double, and double complex xectors
    are supported, but code is in place to support all the main CUDA
    numeric types and nested xectors.

  - Data-loading functions to fill xectors from data in files.

  - Implement loadable modules and wrap libraries like cub, cublas,
    cufft, cusparse, etc.  Make CUDA library reuse as trivial as
    possible.

  - Inlining CUDA C kernels for hand-tuning performance.

  - "Xappings": cuda distributed hash tables that can be indexed by a
    key as well as position.

  - Native graph types.

  - Compile S-expressions directly to CUDA PTX assembly.

## Alpha, Dot, and Beta

The book and paper cited above expressed parallelism using a Lisp
macro-like parallel expression syntax with three operators, alpha,
dot, and beta.  Implementing these operators in hillisp is certainly a
goal, but I'm not positive it can be done efficiently yet without a
new feature in CUDA called dynamic parallelism, which requires a
greater compute capability than any devices I have available to me at
the moment.  Feel free to send me a dual-maxwell system and I'll get
it done. :)


## Reference

Check out [core tests](test/test.lsp) and [xector tests](test/xector.lsp).

## Core

### (is x y)

Are 'x' and 'y' the same symbol?

### (isinstance x y)

Is 'x' an instance of type 'y'?

### (type x)

Return the type of 'x'.

### (quote x)

Return 'x' without evaluating it.

### (eval x)

Eval list the list 'x'.

### (apply x args)

Apply 'args' to the lambda expression 'x-.

### (assert x)

Assert 'x' is true.

### (asserteq x y)

Assert 'x' equals 'y' by comparison ('==').

### (assertall x)

Assert all elements in 'x' are true.

### (assertany x)

Assert at least one element in 'x' is true.


##List

### (car x)

Return the first element of the list 'x'.

### (cdr x)

Return the rest of the elements in 'x'.

### (cons x y)

Return a pair of 'x' and 'y'.

### (list ...)

Cons all arguments into a list.


## IO

### (print x)

Print 'x'.

### (println x)

Print 'x' on its own line.

### (printsp x)

Print 'x' then a space.


## Math

### (+ x y)

Add 'x' and 'y', may be numbers or xectors.

### (+= x y)

In-place add 'x' and 'y' storing the result in 'x', may be numbers or
xectors.

### (- x y)

Subtract 'y' from 'x', may be numbers or xectors.

### (-= x y)

In-place subtract 'y' from 'x' storing the result in 'x', may be
integers or xectors.

### (* x y)

Multiply 'x' and 'y', may be numbers or xectors.

### (*= x y)

In-place multiple 'y' and 'x' storing the result in 'x', may be
integers or xectors.

### (/ x y)

Divide 'x' by 'y', may be numbers or xectors.

### (/= x y)

In-place divide 'x' by 'y' storing the result in 'x', may be
numbers or xectors.

### (fma x y z)

Fused-multiply add 'x * y + z', may be numbers or xectors.

### (fma= x y z)

Fused-multiply add 'x * y + z' storing result in 'x', may be numbers
or xectors.


## Comparison

### (== x y)

Compare 'x' and 'y' for equality.

### !=

### >

### <

### min

### max

### sum


## Logic

### not

### and

### all

### any

### or


# Names

### (set name value)

Binds 'value' to 'name' in the current scope.

### (len l)

Returns the length of the list or xector, otherwise nil.

### (range start stop step)

Cons a list of integers in the given range.

### (def name (args) (body ...))

Bind the function taking 'args', defined by 'body', to 'name'.


## Flow Control

### (if cond (exp ...) [(exp ...)])

### (while cond (exp ...))

### (do start end (exp ...))

### (for i start end (exp ...))

### (collect value)


## Xectors

### (fill value size)

Create a new xector of 'type' with size 'size' and fill each element
with 'value'.  The type of 'value' determines the type of the
xector. 'size' can be an integer (one-dimensional xector) or list of
dimensions, ie '(3 3)' creates a 3x3 two-dimensional xector.

### (empty type size)

Like 'fill', but returns an uninitialized xector where no value is
provided or filled into the new xector. 'type' determines the type of
the xector.

### (copy x y)

Copy the contents of xector 'x' into xector 'y'.  The two xectors must
have the same shape.

### (slice x shape)

Slice the xector 'x' to the specific 'shape'.  'shape' must match the
leading dimensions of 'x'.

### (swap x y)

Swap the contents of 'x' and 'y'.

## Misc

### (dir)

Show all the bound names.

### (time)

Return the time in microseconds since the epoch.

### (gc)

Trigger garbage collection.

