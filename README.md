# SERVER-CLIENT_USING_TCP

The main purpose is to design and implement a web server and client system that can be used to transfer string of data. In this software, the client and the server will build a communication via TCP sockets.

The client and server will pair where server simply echoes the message or instructions that the client sends. Once the connection is built between client and server, we will focus on transferring the data string.

# Authors

- Hitin Sarin -hitinsarin@cmail.carleton.ca
- Jaspreet Kaur -Jaspreetkaur4@cmail.carleton.ca
- Prerit Sikerwal -preritsikerwal@cmail.carleton.ca
- Saksham Mal -sakshammal@cmail.carleton.ca 

# Installation

For installation, steps should be followed from [Installation_File.pdf](https://github.com/jaskaur7/Group_A_SERVER-CLIENT_USING_TCP/blob/master/doc/installation_file.pdf)

# Usage

For successful run, then you can follow instructions mentioned in [user_manual.docx](https://github.com/jaskaur7/Group_A_SERVER-CLIENT_USING_TCP/blob/master/doc/user_manual.pdf)

# File Strucutre
1.	bin: This folder has executable and data file.

2.	build: This folder has all the object files generated using makefile. 

3.	doc: It consists of all the documents for this project.
3.1	user_manual
3.2	installation_file
3.3

4.	include: It has the essential header files to run this project.

5.	lib: It contains the file for implementing the queue.
5.1.	queue.c

6.	src: It has following .c files:
6.1.	server-singlethread
	a)	server.c
6.2.	server-multithread
	a)	server.c
6.3.	client
	a)	client.c

6.	test: It has the files for different test case scenarios.
6.1.	src
	a)	test_client.c
	b)	test_server.c

# For Developers

Developer manual is available [here]()

# License

This project is licensed under the GPL 2.0 License - see the LICENSE.md file for details.

# Acknowledgements

We are thankful to Dr. Cristina Ruiz Martin for providing great guidance on how to develop the software.
