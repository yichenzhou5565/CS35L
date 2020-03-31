#if no operand, act as in current directory                                       
                                                                                   

right='^[\_a-zA-Z]{1}[-\_\.a-zA-Z]{0,13}$'
helper=66

if [ $# -eq 0 ]
then
    D=.


#if two operand, stderr and exit                                                 
                                                                                   
elif [ $# -gt 2 ]
then
    echo "Too many operand." >&2
    exit


#    helper=66                                                                    
                                                                                   
#    echo $helper                                                                 
                                                                                   
#if two operand, decide if the first is -r or not                                 
                                                                                   
elif [ $# -eq 2 ]
then
    if [ $1 != "-r" ]
    then
        echo "Too many operand." >&2
        exit
    else
        D="$2"
        helper=82
    fi



#if a single operand, but the first char is '-'                                   
                                                                                   
elif [ $# -eq 1 ]
then
    if ! [[ "$1" == "-r" ]]; then
	D=$1
    else
        D=.
	helper=82
    fi
fi

if [[ $D == "-"* ]]
then
        echo "Directory starting with -." >&2
        exit
fi

if [ ! -d "$D" ]  #如果他是symbolic link的话，不知道为什么，-d会显示他是个directory
then                 #所以建议把 [ -L "$D" ]加上
        echo "Directory does not exist." >&2
fi

#Now start checking the file name                                                           
basic_poornames()
{
    name=$(basename "$1") #这个地方在$1两边需要有双引号，不然如果是一个奇怪的东西的话，basename会把它当作option的
    if [[ "${name:0:1}" == "-" ]]
    then
        isValid="no"
    #check .                                                                                
    elif [[ ${name:0:1} == "." ]]
    then
         if [[ "$name" == "." ]] || [[ "$name" == ".." ]]
         then
             isValid="yes"
         else
             isValid="no"
         fi
         #check if the length is greater than 14                                            
    elif [ ${#name} -gt 14 ]
    then
        isValid="no"
    else
        isValid="yes"

    fi

    if [[ $isValid == "yes" ]]
    then
        if [[ "$name" =~ ^([\_a-zA-Z]{1}[-\_\.a-zA-Z]{0,13})$ ]];then
            :
        else
            isValid="no"
        fi
    fi

    if [[ $isValid == "no" ]]
    then
        echo "$1""/""$name" #有个小问题，如果"$1"最后是一个"/"的话, 是不能再在$name前面加/的，，这个你就调一调吧，不是很复杂

    fi
}

recursion()
{
    for entry in "$1"/*
    do
	echo 233 $entry
	if ! [[ $entry == "." ]]; then #你这个"$1"/*貌似会把.也给找出来
            basic_poornames "$entry" # 有一个非常严重的问题，entry如果是文件不是目录的话呢，这个你可能需要好好改改
	fi
    done
    # 我跟你说去掉helper容易是因为你这么写就好了
    # for filename in ` ls -a $1 | grep -E $right | sort -f | uniq -D -i  `
    # do ...... done
    ls -a $1 | grep -E $right | sort -f | uniq -D -i >caseHelper_r
    while read filename
    do
        echo ".""/""$filename"
    done <caseHelper_r

    if [ $isValid == "yes" ]
    then


#        if [[ -f $1 ]]                                                                     
#        then                                                                               
	   #  :
#        else                                                                               
#            one_level=$( find $1 -maxdepth 1 -type d )                                     
#            dir=($one_level)                                                               
        for i in $( find "$1" -maxdepth 1 -type d )
        do
            if ! [[ "$i" == "$1" ]] && [ ! -L "$i" ];then
                recursion "$i"
            fi
	    
#                recursion "$i"                                                             
        done
else
        echo "$entry""/""$1"
    fi

}
if [[ $helper -eq 82 ]]
then

    recursion $D
elif [[ $helper -eq 66 ]]
then

    ls -a $D | grep -E $right | sort -f | uniq -D -i >caseHelper
    while read filename
    do
       # echo "*****************"                                                           
        echo "$D""/""$filename"
    done <caseHelper

    for entry in "$D"/*
    do
        basic_poornames $entry
    done

fi
