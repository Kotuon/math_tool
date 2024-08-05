# Bezier Curve Graphing Calculator
![](https://github.com/Kotuon/math_tool/main/math_tool_gif.gif)

## Table of Contents
* [Introduction](#introduction)
* [Technology Used](#technology-used)
* [Requirements](#requirements)
* [Features](#features)
* [References](#references)

## Introduction

I created this small program to quickly visualize Bezier Curves and export the control point values to a CSV. My motivation for making this tool was to have a streamlined process for creating a curve and then using it in an interpolation system I made for Unreal Engine 5. 

For computing the curve, I used De Casteljau's algorithm with binomial coefficients that are calculated at the start of the program.

## Technology Used
* C++
* JUCE
* CMAKE

## Requirements
Built for Windows 10 using CMake.

## Features
* Up to 14 control points in bezier curve.
* Export control point values to csv.
