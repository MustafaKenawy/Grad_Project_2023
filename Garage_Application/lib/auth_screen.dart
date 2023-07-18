import 'dart:io';

import 'auth_form.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';

// ignore_for_file: prefer_const_constructors

class AuthScreen extends StatefulWidget {
  @override
  State<AuthScreen> createState() => _AuthScreenState();
}

class _AuthScreenState extends State<AuthScreen> {


  bool _isLoading = false;
  void submitAuth(String userName, String password, String email, bool isLogin,
      BuildContext ctx,String carNumber) async {
    final _auth = FirebaseAuth.instance;
    try {
      if (isLogin) {
        setState(() {
          _isLoading = true;
        });
        await _auth.signInWithEmailAndPassword(
          email: email,
          password: password,
        );
      } else {
        setState(() {
          _isLoading = true;
        });
        await _auth.createUserWithEmailAndPassword(
          email: email,
          password: password,
        );


      await FirebaseFirestore.instance
          .collection('users')
          .doc(_auth.currentUser?.uid)
          .set({
        'email': email,
        'userName': userName,
        'password': password,
        'carNumber' :carNumber,
        'admin':false,
        'carIndex':'8',
      });}
    } on FirebaseAuthException catch (err) {
      setState(() {
        _isLoading = false;
      });
      var message = 'An error occurred ,please check your data';
      if (err.message != null) {
        message = err.message!;
      }
      ScaffoldMessenger.of(ctx).showSnackBar(SnackBar(
        content: Text(
          message,
          style: TextStyle(
            fontSize: 15,
          ),
        ),
        backgroundColor: Theme.of(ctx).colorScheme.error,
      ));
    } catch (err) {
      setState(() {
        print(err);
        _isLoading = false;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: AuthForm(submitAuth, _isLoading),
    );
  }
}
