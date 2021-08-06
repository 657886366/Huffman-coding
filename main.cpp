//
//  main.cpp
//  Project   quad tree
//
//  Created by Conghui Deng on 2/23/20.
//  Copyright © 2020 Conghui Deng. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class HtreeNode{
public: string chStr;
        int prob;
        string code;
        HtreeNode *left;
        HtreeNode *right;
        HtreeNode *next;
        HtreeNode(){
        
    }
        HtreeNode(string c,int p, string cd,HtreeNode *l,HtreeNode *r,HtreeNode *n){
        chStr=c;
        prob=p;
        code=cd;
        left=l;
        right=r;
        next=n;
    }
        void printNode(HtreeNode *T,ofstream &out){
            out<<"("<<T->chStr<<", "<<T->prob<<", "<<T->code<<", ";
            if(T->next!=NULL)
                out<<T->next->chStr;
                else
                    out<<"NULL";
            if(T->left!=NULL && T->right!=NULL)
                out<<", "<<T->left->chStr<<", "<<T->right->chStr<<")";
            else
                out<<", NULL, NULL)";
    }
};

class linkedList{
public:
    HtreeNode *listHead;
    linkedList(){
        
    }
    HtreeNode *listInsert(HtreeNode *listHead,HtreeNode *newNode){
        HtreeNode *spot=new HtreeNode();
        spot=findSpot(listHead,newNode);
        newNode->next=spot->next;
        spot->next=newNode;
        return listHead;
    }
    HtreeNode *findSpot(HtreeNode *listHead,HtreeNode *newNode){
        HtreeNode *temp=listHead;
        while(temp->next!=NULL && temp->next->prob<=newNode->prob){
            temp=temp->next;
        }
        return temp;
    }
    void printList(HtreeNode *listHead,ofstream &out){
        HtreeNode *temp=listHead;
        while(temp->next!=NULL){
            temp->printNode(temp,out);
            temp=temp->next;
            out<<"->";
        }
        temp->printNode(temp,out);
        out<<"->NULL"<<endl;
    }
};

class HuffmanBinaryTree{
public:
    HuffmanBinaryTree(){
        
    }
    HtreeNode *constructHuffmanLList(ifstream &in, ofstream &out){
        HtreeNode *listHead=new HtreeNode("dummy",0,"0",nullptr,nullptr,nullptr);
        string data;
        string chr;
        int prob;
        linkedList *ll=new linkedList();
        HtreeNode *newNode=new HtreeNode();
        while(in>>data){
            chr=data;
            if(in>>data){
            prob=stoi(data);
            newNode=new HtreeNode(chr,prob,"",nullptr,nullptr,nullptr);
            listHead=ll->listInsert(listHead,newNode);
            ll->printList(listHead,out);
            }
        }
        return listHead;
    }
    HtreeNode *constructHuffmanBinTree(HtreeNode *listHead,ofstream &out){
        HtreeNode *temp=listHead->next;
        int prob;
        string chr;
        string code;
        HtreeNode *newNode;
        linkedList *ll=new linkedList();
        while(listHead->next->next!=NULL){
            prob=temp->prob+temp->next->prob;
            chr=temp->chStr+temp->next->chStr;
            code=temp->code+temp->next->code;
            newNode=new HtreeNode(chr,prob,code,temp,temp->next,NULL);
            listHead=ll->listInsert(listHead,newNode);
            listHead->next=listHead->next->next->next;
            ll->printList(listHead,out);
            temp=listHead->next;
        }
        return listHead->next;
    }
    void preOrderTraversal(HtreeNode *T,ofstream &out){
//        if(T==NULL){
//            out<<NULL;
//        }
        if(isLeaf(T)){
            T->printNode(T,out);
            out<<"->";
        }
        else{
        T->printNode(T,out);
            out<<"->";
        preOrderTraversal(T->left,out);
        preOrderTraversal(T->right,out);
        }
    }
    void inOrderTraversal(HtreeNode *T,ofstream &out){
        if(isLeaf(T)){
            T->printNode(T,out);
            out<<"->";
        }
        else{
        inOrderTraversal(T->left,out);
        T->printNode(T,out);
            out<<"->";
        inOrderTraversal(T->right,out);
        }
    }
    void postOrderTraversal(HtreeNode *T,ofstream &out){
        if(isLeaf(T)){
            T->printNode(T,out);
            out<<"->";
        }
        else{
        postOrderTraversal(T->left,out);
        postOrderTraversal(T->right,out);
        T->printNode(T,out);
            out<<"->";
        }
    }
    void constructCharCode(HtreeNode *T,string code,ofstream &out){
        if(isLeaf(T)){
            T->code=code;
            out<<"("<<T->chStr<<", "<<T->code<<")"<<endl;
        }
        else {
        constructCharCode(T->left,code+"0",out);
        constructCharCode(T->right,code+"1",out);
        }
    }
    bool isLeaf(HtreeNode *node){
        if(node->left==NULL && node->right==NULL)
        return true;
        return false;
    }
};
int main(int argc, const char *argv[]){
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);
    ofstream outFile3(argv[4]);
    HuffmanBinaryTree *bt=new HuffmanBinaryTree();
    HtreeNode *listHead=new HtreeNode();
    listHead=bt->constructHuffmanLList(inFile,outFile3);
    linkedList *ll=new linkedList();
    ll->printList(listHead,outFile2);
    HtreeNode *root=new HtreeNode();
    root=bt->constructHuffmanBinTree(listHead,outFile3);
    outFile2<<"PreOrder: "<<endl;
    bt->preOrderTraversal(root, outFile2);
    outFile2<<"NULL"<<endl<<"InOrder: "<<endl;
    bt->inOrderTraversal(root, outFile2);
    outFile2<<"NULL"<<endl<<"PostOrder: "<<endl;
    bt->postOrderTraversal(root, outFile2);
    outFile2<<"NULL"<<endl;
    bt->constructCharCode(root, "", outFile1);
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
}
