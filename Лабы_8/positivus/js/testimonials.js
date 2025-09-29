document.addEventListener("DOMContentLoaded", function () {
  const track = document.querySelector(".testimonials-track");
  const slides = document.querySelectorAll(".testimonials-block-comment");
  const dots = document.querySelectorAll(".slider-dot");
  const prevBtn = document.querySelector(".prev-btn");
  const nextBtn = document.querySelector(".next-btn");

  let currentSlide = 0;
  const slideCount = slides.length;

  // Функция для обновления позиции слайдера
  function updateSliderPosition() {
    track.style.transform = `translateX(-${currentSlide * 100}%)`;

    // Обновляем активную точку
    dots.forEach((dot, index) => {
      dot.classList.toggle("active", index === currentSlide);
    });

    // Обновляем состояние кнопок
    prevBtn.disabled = currentSlide === 0;
    nextBtn.disabled = currentSlide === slideCount - 1;
  }

  // Переход к следующему слайду
  function nextSlide() {
    if (currentSlide < slideCount - 1) {
      currentSlide++;
      updateSliderPosition();
    }
  }

  // Переход к предыдущему слайду
  function prevSlide() {
    if (currentSlide > 0) {
      currentSlide--;
      updateSliderPosition();
    }
  }

  // Переход к конкретному слайду
  function goToSlide(index) {
    currentSlide = index;
    updateSliderPosition();
  }

  // Автоматическое перелистывание
  let autoSlideInterval = setInterval(nextSlide, 5000);

  // Остановка автоматического перелистывания при взаимодействии
  function resetAutoSlide() {
    clearInterval(autoSlideInterval);
    autoSlideInterval = setInterval(nextSlide, 5000);
  }

  // Назначаем обработчики событий
  nextBtn.addEventListener("click", function () {
    nextSlide();
    resetAutoSlide();
  });

  prevBtn.addEventListener("click", function () {
    prevSlide();
    resetAutoSlide();
  });

  dots.forEach((dot, index) => {
    dot.addEventListener("click", function () {
      goToSlide(index);
      resetAutoSlide();
    });
  });

  // Обработка клавиатуры
  document.addEventListener("keydown", function (e) {
    if (e.key === "ArrowLeft") {
      prevSlide();
      resetAutoSlide();
    } else if (e.key === "ArrowRight") {
      nextSlide();
      resetAutoSlide();
    }
  });

  // Инициализация слайдера
  updateSliderPosition();
});
