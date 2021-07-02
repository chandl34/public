package com.chandl34.weatheralerts.ui.activity

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.chandl34.weatheralerts.R
import com.chandl34.weatheralerts.data.User

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val user1 = User("Jane", "Doe");
        val user2 = User("Jane", "Doe");
        val structurallyEqual = user1 == user2 // true
        val referentiallyEqual = user1 === user2 // false

        val jane = User(lastName = "Doe");
        val john = User("John", "Doe");




        System.out.println("done, son")
    }
}