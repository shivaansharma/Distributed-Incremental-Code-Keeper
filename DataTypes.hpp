enum class commands{ // scoped enum 
    BAD_COMMAND,
    add ,
    catFile,
    checkIgnore,
    checkout,
    commit,
    hashObject,
    init,
    log,
    lsFiles,
    lsTree,
    revParse,
    rm,
    showRef,
    status,
    tag,
};// had to make an enum becauuse switch uses an integral type and arcv is a c style string 
enum class objectType{
    BADTYPE,
    BLOB,
    TAG,
    COMMIT,
    TREE
};