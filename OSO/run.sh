./osocompiler < $1
mkdir output
mv output.java output
cd output
javac -g output.java
java -classpath : output