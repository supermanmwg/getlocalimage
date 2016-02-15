/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <sys/socket.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "com_example_weiguangmeng_activitytest_SocketActivity.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */

JNIEXPORT jstring JNICALL Java_com_example_weiguangmeng_activitytest_SocketActivity_stringFromJNI
        (JNIEnv *env, jobject this) {
    return (*env)->NewStringUTF(env, "Hello from JNI !");
}

JNIEXPORT void JNICALL Java_com_example_weiguangmeng_activitytest_SocketActivity_setClientSocket
        (JNIEnv *env, jobject this) {
    __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "set client side");

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    portno = 51717;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname("localhost");
    if (server == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "ERROR, no such host\n");
        exit(0);
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", " host is established\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "ERROR connecting");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "client connecting");
    }

    bzero(buffer,256);
    bcopy("hello is client side",buffer, 256);

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "ERROR writing to socket");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "writint to socket");
    }
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "ERROR reading from socket");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "reading from socket");
    }
    __android_log_print(ANDROID_LOG_INFO, "-----from--client--jni-------", "client from server %s",buffer);
    close(sockfd);

}

JNIEXPORT void JNICALL Java_com_example_weiguangmeng_activitytest_SocketActivity_setServerSocket
        (JNIEnv *env, jobject this) {
    __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "set server side");

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "ERROR opening socket");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 51717;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "ERROR on binding");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "binding is suceessful");
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "ERROR on accept");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", " accept is successful");
    }

    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "ERROR reading from socket");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "reading from socket is successful");
    }

    __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "Here is the message: %s\n",buffer);

    n = write(newsockfd,"I got your message",18);

    if (n < 0)  {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", "ERROR writing to socket");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "-----from--server--jni-------", " writing to socket is successful");
    }
    close(newsockfd);
    close(sockfd);
}