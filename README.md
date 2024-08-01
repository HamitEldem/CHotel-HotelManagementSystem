# CHotel-HotelManagementSystem

This project is a Hotel Management System programmed in C and OpenGL GLUT. The system includes basic functionalities for managing hotel operations, with plans to expand its capabilities in the near future.

## Table of Contents

Purpose<br />
Overview<br />
Current Functionalitie<br />
Prerequisite<br />
Modules<br />
Future Work<br />
Project Vision<br />
Contributing<br />
License<br />


## Purpose

The primary aim of this project is to implement and demonstrate the C programming skills I acquired in my coursework at **CTIS 151** (Introduction to Programming) and **CTIS 152** (Data Structures and Algorithms). This Hotel Management System serves as a comprehensive showcase of my proficiency in various C programming concepts such as control flow, dynamic memory allocation, arrays, matrices, loops, stacks, queues, linked lists, and other fundamental programming topics.

In addition to my C programming expertise, this project integrates knowledge from **CTIS 164** (Technical Mathematics with Programming), where I learned to develop GLUT-based projects, which form the backbone of this system. Moreover, it incorporates foundational SQL skills from **CTIS 165** (Fundamentals of Information Systems), providing a basic introduction to SQL.

To complement my SQL knowledge and enhance the database aspects of this project, I utilized ChatGPT for generating the necessary CSV files and designing database schemas according to my specifications. While I received assistance with some SQLite codes, I strived to write most SQL statements myself, leveraging my understanding of query writing, reading, and updating data. This project not only showcases my technical abilities but also reflects my initiative in seeking help and learning new tools to create a robust application. 

## Overview

The HMS (Hotel Management System) project aims to provide a robust and user-friendly application for managing hotel operations. The system leverages C for core functionality and OpenGL GLUT for graphical user interface elements.

## Current Functionalities

### User Interface
**Welcome Screen:** Displays a welcome message when the application starts.<br />
**Login Screen:** Allows users to log in with an ID and password. The system validates the user credentials against a SQLite database.<br />
**User Screen:** Displays user-specific information once logged in. The sidebar and profile bar are dynamically generated based on user data.<br /><br />

### Database Interaction
**User Validation:** Validates user credentials against stored data in the SQLite database.<br />
**User Information Retrieval:** Retrieves user information (name and surname) from the SQLite database based on user ID.<br /><br />

### Input Handling
**Keyboard Functions:** Captures keyboard inputs to handle user interactions.<br />
**Login Input:** Handles input for user ID and password during login.<br />
**Navigation:** Uses keyboard inputs to navigate through different screens and options within the application.<br />

## Prerequisites

Ensure you have the following libraries installed:

**OpenGL<br />
GLUT<br />
SQLite<br />**

## Application Flow
**Welcome Screen:** The application starts with a welcome screen.
**Login Screen:** After the welcome screen, users are prompted to log in.
**User Screen:** Upon successful login, the user-specific interface is displayed.

## Modules

### Housekeeping
The housekeeping module manages housekeeping tasks and schedules.<br />

### Kitchen
The kitchen module integrates functionalities for menu management and order tracking.<br />

### Management
The management module includes features for overseeing hotel operations.<br />

### Accounting
The accounting module manages financial records, invoicing, and reporting.<br />

### Purchasing
The purchasing module handles supplies and procurement processes.<br />

### Sales
The sales module includes tools for boosting hotel bookings and managing customer relations.<br />

## Future Work

### Near Future
**Database Modifications:**
Add new columns to existing tables to enhance data storage capabilities.
Ensure backward compatibility with existing data.<br />
**Front Office Module:**
Develop and integrate a front office module for managing reservations, check-ins, and check-outs.
Interface enhancements for better user interaction.<br />
### Up Next
**Housekeeping Module:** Develop functionalities for managing housekeeping tasks and schedules.<br /><br />
**Kitchen Module** Integrate kitchen management functionalities, including menu management and order tracking.<br /><br />
**Management Module:** Implement management-specific features for overseeing hotel operations.<br /><br />
**Accounting Module:** Develop an accounting system for managing financial records, invoicing, and reporting.<br /><br />
**Purchasing Module:** Integrate functionalities for managing supplies and procurement processes.<br /><br />
**Sales Module:** Develop sales and marketing tools to help boost hotel bookings and manage customer relations.<br /><br />

### Future Enhancements
**Password Hashing:** Implement password hashing to enhance security for user credentials.<br />

## Project Vision

When all code is done, the HMS project will offer a comprehensive hotel management solution, including:

**User Authentication:** Secure login and role-based access control.<br />
**Reservation System:** Full-featured reservation management, including online booking capabilities.<br />
**Guest Management:** Detailed guest profiles, history, and preferences.<br />
**Room Management:** Real-time room status updates, housekeeping schedules, and maintenance tracking.<br />
**Billing and Invoicing:** Automated billing, payment processing, and financial reporting.<br />
**Reporting and Analytics:** Advanced reporting tools to provide insights into hotel operations and performance.<br />

## Contributing

**Contributions are welcome!** To contribute:

**Fork** the repository.<br />
**Create a new branch**<br />
**Commit** your **changes**<br />
**Push** to the branch <br />
**Create** a new **Pull Request.**<br />

## License

This project is licensed under the MIT License. See the LICENSE file for details.
