﻿#-*- coding: utf-8 -*-

class Queue:

    def __init__(self):
        self.qList = []
    
    def enqueue(self, item):
        self.qList.append(item)

    def dequeue(self):
        item = self.qList[0]
        self.qList = self.qList[1:]
        return item

    def head(self):
        return self.qList[0]

    def isEmpty(self):
        return len(self.qList) == 0