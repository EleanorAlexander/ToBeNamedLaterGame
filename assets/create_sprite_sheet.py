import os
import argparse
from PIL import Image

def generate_spritesheet(image_folder, output_image, output_txt):
    # Get list of image files
    image_files = [f for f in os.listdir(image_folder) if f.endswith('.png')]
    
    # Sort files by their naming convention (row, column)
    image_files.sort()
    
    # Load first image to get dimensions
    first_image = Image.open(os.path.join(image_folder, image_files[0]))
    width, height = first_image.size
    
    # Calculate the dimensions of the spritesheet
    max_row = max(int(f.split('x')[0]) for f in image_files) + 1
    max_col = max(int(f.split('x')[1].split()[0]) for f in image_files) + 1
    
    # Create an empty spritesheet
    spritesheet = Image.new('RGBA', (max_col * width, max_row * height))
    
    # Open the output text file
    with open(output_txt, 'w') as txt_file:
        # Loop through the image files and paste them into the spritesheet
        for image_file in image_files:
            # Extract row and column from the filename
            parts = image_file.split('x')
            row = int(parts[0])
            col = int(parts[1].split()[0])
            name = parts[1].split()[1]
            
            # Open image and paste it into the spritesheet
            img = Image.open(os.path.join(image_folder, image_file))
            spritesheet.paste(img, (col * width, row * height))
            
            # Write to the text file
            txt_file.write(f"{name} {row} {col} {width}x{height}\n")
    
    # Save the spritesheet
    spritesheet.save(output_image)

def main():
    parser = argparse.ArgumentParser(description="Generate a spritesheet from separate PNG files.")
    parser.add_argument("image_folder", help="Folder containing the sprite images.")
    parser.add_argument("output_image", help="Filename for the output spritesheet PNG.")
    parser.add_argument("output_txt", help="Filename for the output text file with positions.")
    
    args = parser.parse_args()
    
    generate_spritesheet(args.image_folder, args.output_image, args.output_txt)

if __name__ == "__main__":
    main()
