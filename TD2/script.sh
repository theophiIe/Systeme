cd /tmp
mkdir project/doc project/include project/src -p
cd project
echo "Molinatti Théophile" > README
touch include/func.h src/main.c src/func.c
ls -R > content.txt
cd ..
mv project projectV2
zip pv2.tar projectV2 -r

