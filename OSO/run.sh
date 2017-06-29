./osocompiler < $1
mv output.java output
cd output
javac -g output.java
java -classpath : output