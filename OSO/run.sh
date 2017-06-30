./osocompiler < $1
mkdir -p output
mv output.java output
cd output
javac -g output.java
java -classpath : output