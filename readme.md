**The project is an implementaio of the article**

**<a href = "https://wyag.thb.lt/#intro">Write yourself a Git!</a>**

This project is being created for me to understand cpp to a better level get how git works and also understand the tools 
tools used
<ul>
<li>Make
<li>GDB
<li>Valgrind
<li>C++ 17
</ul>
The og article is written in <i><b>python</b></i> this is my implementation of it in <i><b>cpp</i></b>

### notes ###
 <ul>
    <li>At its core, Git is a “content-addressed filesystem”. That means that unlike regular filesystems, where the name of a file is arbitrary and unrelated to that file’s contents, the names of files as stored by Git are mathematically derived from their contents.
    <li><b>GiT obbject -> </b> files in the git repository, whose paths are determined by their contents.


 </ul>

 ### Implementing the sha 1 function ###
 <span>
   SHA stands for secure hash algo <br>
   it creates a 160 bit digest , renders as a 40 digit hexadecimal
   <br>
   <ol>
   <li>break the input int n parts 448 bits each
   <li> add a 64 bit padding to each part to make them 512 bits
   <li> these 512 bits are passed to the compression function along with the 160 bit output , we have a default value for the output.
   <li> 80 rounds of compression
   </ol>
</span>
  <b>MATH</b><br>
   ill be using 8 bit integer for the implementtaion uint_8
   so 448/8 = 56 ill have to divide it in 56 bytes and then additional paddind would be used 