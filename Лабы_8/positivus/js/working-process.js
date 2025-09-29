document.addEventListener("DOMContentLoaded", () => {
        const content = document.getElementsByClassName(
          "working-process-block-card-drop-down-text"
        );
        const buttons = document.getElementsByClassName(
          "working-process-block-card-text__button"
        );
        const image = document.getElementsByClassName(
          "working-process-block-card-text__icon"
        );
        const card = document.getElementsByClassName(
          "working-process-block-card"
        );

        let buttonsArray = Array.from(buttons);
        let contentArray = Array.from(content);
        let imageArray = Array.from(image);
        let cardArray = Array.from(card);

        console.log(buttonsArray);

        buttonsArray.forEach((button, idx) => {
          console.log(button);
          button.addEventListener("click", function (event) {
            console.log(contentArray[idx]);
            if (
              contentArray[idx].style.display === "none" ||
              contentArray[idx].style.display === ""
            ) {
              contentArray[idx].style.display = "block";
              imageArray[idx].src =
                "/img/working-process/working-process-minus-icon.png";
              cardArray[idx].style.backgroundColor = "#b9ff66";
            } else {
              contentArray[idx].style.display = "none";
              imageArray[idx].src =
                "/img/working-process/working-process-plus-icon.png";
              cardArray[idx].style.backgroundColor = "#f3f3f3";
            }
          });
        });
      });