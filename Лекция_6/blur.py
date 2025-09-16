# Blurs an image

from PIL import Image, ImageFilter

# Blur image
before = Image.open("stadium.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")
