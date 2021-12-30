"use strict";

function check_pt1_answer(btnElement) {
  const message1 = document.getElementById("message1");
  if (btnElement.id !== "3") {
    give_feedback(btnElement, "red", message1, "Incorrect!");
  } else {
    give_feedback(btnElement, "green", message1, "Correct!");
  }
}

function check_pt2_answer() {
  const answerElement = document.querySelector("#answer_pt2");
  const message2 = document.getElementById("message2");
  if (answerElement.value !== "1954") {
    give_feedback(answerElement, "red", message2, "Incorrect!");
  } else {
    give_feedback(answerElement, "green", message2, "Correct!");
  }
  return;
}

function give_feedback(element, color, messageElement, message) {
  element.style.color = color;
  messageElement.innerHTML = message;
  messageElement.style.color = color;
}
