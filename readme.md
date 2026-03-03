**The project is an implementaio of the article**

**<a href = "https://wyag.thb.lt/#intro">Write yourself a Git!</a>**

This project is being created for me to understand cpp to a better level get how git works and also understand the tools 
tools used
<ul>
<li>Make
<li>LLDB
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
SHA stands for Secure Hash Algorithm.<br>
SHA-1 produces a 160-bit digest, which is rendered as a 40-character hexadecimal string.
   <br>
   <b>Algorithm Overview</b>
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
  <br> 
  <b>Problems faced</b>
  <br> 
  There where some issues with the sha 1 first , i mostly vibe coded it , but got the understanding how it works ,
  the problem was it was ment to take in a file path but turns out it was not needed fixed that rest is the standard algo

### Git Repo and the init command ###
 note -> when i say git it means dick (using git is causing name confilcts )
<ol>
<li>A git repo is made up of two things a work Tree and a git directory 
   <ul>
   <li>
   <b>Work Tree -</b> where the files ment to be version controlled live
   </li>
   <li>
   <b>Git dir -</b> where Git stores its own data 
   </li>
   </ul>
</li>
<li>
   <b>Git dir compries of</b>
   <ul>
   <li>objects</li>
   <li>refs
    <ul>
    <li>heads</li>
    <li>tags</li>
    </ul>
   </li>
   <li>HEAD</li>
   <li>config -> holdes ini like files </li>
   <li>description -> holdes description</li>
   <ul>
</li>

</ol>


hello from new branch