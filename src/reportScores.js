const nodemailer = require('nodemailer');
require('dotenv').config();

// Function to send email
async function sendEmail(submissionInfo) {

    console.log("sendemail was proc");
    // Create a transporter object using SMTP transport
    let transporter = nodemailer.createTransport({
        service: 'gmail', // Use your email service
        auth: {
            user: process.env.EMAIL_USER, // Your email
            pass: process.env.EMAIL_PASS // Your email password
        }
    });

    // Email content
    let mailOptions = {
        from: process.env.EMAIL_USER, // Sender address
        to: process.env.PROFESSOR_EMAIL, // List of recipients
        subject: 'Exam Submission', // Subject line
        text: `${submissionInfo}` // Plain text body
    };

    // Send the email
    try {
        await transporter.sendMail(mailOptions);
        console.log('Email sent successfully');
    } catch (error) {
        console.error('Error sending email:', error);
    }
}

module.exports = sendEmail;


