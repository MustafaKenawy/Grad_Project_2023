import 'dart:async';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

import 'admin_Screen.dart';

class HomeScreen extends StatefulWidget {
  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  final _auth = FirebaseAuth.instance;
  bool alreadyParked = false;
  Future<bool> isAdmin() async {
    late String? uid = _auth.currentUser?.uid;
    var snapshot =
        await FirebaseFirestore.instance.collection('users').doc(uid).get();
    bool isAdmin = snapshot['admin'];
    //admin = isAdmin;
    return isAdmin;
  }

  // late String? uid = _auth.currentUser?.uid;
  // Stream<DocumentSnapshot> snapshot = FirebaseFirestore.instance.collection('users').doc(uid).snapshots();
  // double _currentSliderValue = 10;
  bool admin = false;
  bool main = false;
  DatabaseReference ref = FirebaseDatabase.instance.ref("test");
  void _logOut() {
    _auth.signOut();
  }
  // List<String> arr = ['0','1','2','3','4','5','6','7'];
  bool _isIndex(String str){
    for(int i =0 ; i< 8 ; i++)
      {
        if(str == "$i") {
          return true;
        }
      }
    return false;
  }

  Future<void> _sendCarIndex() async {
    late String? uid = _auth.currentUser?.uid;
    var snapshot =
        await FirebaseFirestore.instance.collection('users').doc(uid).get();
    var carIndex = snapshot['carIndex'];
    await ref.update({
      "carIndex": carIndex.toString(),
    });
    if(int.parse(carIndex) > 0) {
      carIndex =(int.parse(carIndex)).toString();
      await FirebaseFirestore.instance
          .collection('users')
          .doc(_auth.currentUser?.uid)
          .update({
        'carIndex' : carIndex,
      });
    }
  }

  Future<void> _retrieve() async {
    if(alreadyParked){
    alreadyParked = false;
    _showMyDialog("Getting your car, Please Wait!!"); // for fast response only the flag alreadyParked assures the operation
    await ref.update({
      "data": '2',
    });
    Timer(Duration(milliseconds: 1500), () async {
      DataSnapshot data = await ref.get();
      if (data.child("ret").value == 'N')
        _showMyDialog("No car Available");
      else if (data.child("ret").value == 'Y') {
       // _showMyDialog("Getting your car, Please Wait!!");
        _sendCarIndex();
      } else {
        _showMyDialog("No car Available");
      }});
    }
    else{
      _showMyDialog("No car Available");
    }
  }

  Future<void> _check() async {
    _showMyDialog("There is An Empty Place");// replacement for fast response
    await ref.update({
      "data": '0',
    });
    return;
    DataSnapshot data = await ref.get();
    if (data.child("empty").value == 'E')
      _showMyDialog("There is An Empty Place");
    else if (data.child("empty").value == 'F')
      _showMyDialog("Sorry the Garage is full");
    else {
      _showMyDialog("Sorry the Garage is full");
    }
  }

  Future<void> _showMyDialog(String txt) async {
    return showDialog<void>(
      context: context,
      barrierDismissible: false, // user must tap button!
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text(
            'Smart Garage',
            style: TextStyle(fontWeight: FontWeight.w600),
          ),
          content: SingleChildScrollView(
            child: ListBody(
              children: <Widget>[
                Text(
                  txt,
                  style: TextStyle(fontSize: 19),
                ),
              ],
            ),
          ),
          actions: <Widget>[
            TextButton(
              child: const Text(
                'OK',
                style: TextStyle(fontSize: 17),
              ),
              onPressed: () {
                Navigator.of(context).pop();
              },
            ),
          ],
        );
      },
    );
  }

  Future<void> _park() async {
    if (!alreadyParked) {
      await ref.update({
        "data": '1',
      });
      DataSnapshot data = await ref.get();
      if (data
          .child("park")
          .value == 'C')
        _showMyDialog("Sorry the Garage is full");
      else if (_isIndex(data
          .child("park")
          .value
          .toString())) {
        _showMyDialog("Parking your Car.....");
        alreadyParked = true;
        Timer(Duration(seconds: 5), () async {
          DataSnapshot data = await ref.get();
          await FirebaseFirestore.instance
              .collection('users')
              .doc(_auth.currentUser?.uid)
              .update({
            'carIndex': data
                .child("park")
                .value,
          });
        });
      }
      else {
        _showMyDialog('No car Available');
      }
    }
    else{
      _showMyDialog('You Already parked your Car!!!!!');
    }
  }

  Future<void> set(BuildContext ctx) async {
    bool f;
    main = !main;
    f = await isAdmin();
    if (f == true) {
      admin = !admin;
      setState(() {});
    } else {
      ScaffoldMessenger.of(ctx).showSnackBar(SnackBar(
        content: const Text(
          "Access Denied",
          style: TextStyle(
            fontSize: 15,
          ),
        ),
        backgroundColor: Theme.of(ctx).colorScheme.error,
      ));
    }
    print(admin);
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.black,
        title: const Text('Smart Garage'),
        actions: [
          IconButton(onPressed: _logOut, icon: const Icon(Icons.logout))
        ],
      ),
      body: admin
          ? AdminScreen()
          : Container(
              color: Colors.black,
              child: Column(
                children: [
                  const SizedBox(
                    height: 70,
                  ),
                  ElevatedButton(
                    onPressed: _check,
                    style: ButtonStyle(
                        backgroundColor:
                            MaterialStateProperty.all(Colors.orangeAccent),
                        shape:
                            MaterialStateProperty.all<RoundedRectangleBorder>(
                                RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(20),
                        ))),
                    child: Container(
                      width: 250,
                      padding: const EdgeInsets.all(10),
                      child: const Center(
                          child: Text(
                        'Check For Empty parking',
                        style: TextStyle(fontSize: 20, color: Colors.black),
                      )),
                    ),
                  ),
                  const SizedBox(
                    height: 70,
                  ),
                  Center(
                    child: ElevatedButton(
                      onPressed: _retrieve,
                      style: ButtonStyle(
                          backgroundColor:
                              MaterialStateProperty.all(Colors.tealAccent),
                          shape:
                              MaterialStateProperty.all<RoundedRectangleBorder>(
                                  RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(20),
                          ))),
                      child: Container(
                        width: 250,
                        padding: const EdgeInsets.all(10),
                        child: const Center(
                            child: Text(
                          'Retrieve your Car',
                          style: TextStyle(fontSize: 20, color: Colors.black),
                        )),
                      ),
                    ),
                  ),
                  const SizedBox(
                    height: 70,
                  ),
                  Center(
                    child: ElevatedButton(
                      onPressed: _park,
                      style: ButtonStyle(
                          backgroundColor:
                              MaterialStateProperty.all(Colors.redAccent),
                          shape:
                              MaterialStateProperty.all<RoundedRectangleBorder>(
                                  RoundedRectangleBorder(
                            borderRadius: BorderRadius.circular(20),
                          ))),
                      child: Container(
                        width: 250,
                        padding: const EdgeInsets.all(10),
                        child: const Center(
                            child: Text(
                          'Park my Car',
                          style: TextStyle(fontSize: 20, color: Colors.black),
                        )),
                      ),
                    ),
                  ),
                  const SizedBox(
                    height: 70,
                  ),
                ],
              ),
            ),
      floatingActionButton: FloatingActionButton.extended(
        label: !main? const Text(
          "Admin",
          style: TextStyle(fontSize: 20),
        ):
        const Text(
          "Main",
          style: TextStyle(fontSize: 20),
        ),
        icon: const Icon(Icons.settings),
        onPressed: () => set(context),
      ),
    );
  }
}
