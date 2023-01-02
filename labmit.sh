find ./srcs/lib -type f -name *.c
read -p "Do you want to continue? [Y/n] " yn
case "$yn" in [yY]*) ;; *) echo "abort." ; exit ;; esac
find ./srcs/lib -type f -name *.c | xargs sed -e "s/.h"/_bonus.h"/g" > tmp
# find ./srcs/lib -type f -name *.c | xargs sed -e "s/_bonus.h"/.h"/g" > tmp
# sed -e "s/。/. /g" tmp > tmp1
# sed -e "s/、/, /g" tmp1 > tmp
# sed -e "s/一つ/1つ/g" tmp > tmp1
# sed -e "s/１/1/g" tmp1 > tmp
# sed -e "s/２/2/g" tmp > tmp1
# sed -e "s/３/3/g" tmp1 > tmp
# rm tmp1
find . -type f -name *.c | xargs mv tmp