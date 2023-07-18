import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

class AdminScreen extends StatelessWidget {
  AdminScreen({Key? key}) : super(key: key);
  DatabaseReference ref = FirebaseDatabase.instance.ref("test");

  Future<void> _up() async {
    await ref.update({
      "data": '3',
    });
  }
  Future<void> _down() async {
    await ref.update({
      "data": '4',
    });
  }
  Future<void> _right() async {
    await ref.update({
      "data": '5',
    });
  }
  Future<void> _left() async {
    await ref.update({
      "data": '6',
    });
  }
  Future<void> _put() async {
    await ref.update({
      "data": '7',
    });
  }
  Future<void> _take() async {
    await ref.update({
      "data": '8',
    });
  }
  Future<void> _stop() async {
    await ref.update({
      "data": '9',
    });
  }

  Future<void> _open() async {
    await ref.update({
      "data": '*',
    });
  }
  Future<void> _close() async {
    await ref.update({
      "data": '#',
    });
  }
  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.black,
      // margin: EdgeInsets.all(20),
      child: Column(
        children: [
          SizedBox(
            height: 70,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: _up,
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStateProperty.all(Colors.greenAccent),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'UP',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
              ElevatedButton(
                onPressed: _down,
                style: ButtonStyle(
                    backgroundColor:
                        MaterialStateProperty.all(Colors.greenAccent),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'Down',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
            ],
          ),
          SizedBox(
            height: 70,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: _right,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.yellow),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'Right',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
              ElevatedButton(
                onPressed: _left,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.yellow),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'Left',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
            ],
          ),
          SizedBox(
            height: 70,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: _put,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.teal),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'Put',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
              ElevatedButton(
                onPressed: _take,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.teal),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(20),
                    ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                    'Take',
                    style: TextStyle(fontSize: 20, color: Colors.black),
                  )),
                ),
              ),
            ],
          ),
          SizedBox(
            height: 70,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: _open,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.deepPurpleAccent),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(20),
                        ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                        'Open',
                        style: TextStyle(fontSize: 20, color: Colors.black),
                      )),
                ),
              ),
              ElevatedButton(
                onPressed: _close,
                style: ButtonStyle(
                    backgroundColor: MaterialStateProperty.all(Colors.deepPurpleAccent),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                        RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(20),
                        ))),
                child: Container(
                  width: 100,
                  padding: const EdgeInsets.all(10),
                  child: const Center(
                      child: Text(
                        'Close',
                        style: TextStyle(fontSize: 20, color: Colors.black),
                      )),
                ),
              ),
            ],
          ),
          SizedBox(
            height: 70,
          ),
          ElevatedButton(
            onPressed: _stop,
            style: ButtonStyle(
                backgroundColor: MaterialStateProperty.all(Colors.red),
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                    RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20),
                ))),
            child: Container(
              width: 250,
              padding: const EdgeInsets.all(10),
              child: const Center(
                  child: Text(
                'Stop All',
                style: TextStyle(fontSize: 20, color: Colors.black),
              )),
            ),
          ),
        ],
      ),
    );
  }
}
