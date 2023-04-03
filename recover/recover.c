#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE thebuffer[512];
    int bytesRead, counter = 0;
    char filename[8];

    FILE *f = fopen(argv[1], "r");
    FILE *img = NULL;

    // showing right usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // showing right usage
    if (f == NULL)
    {
        printf("./recover card.raw");
        return 1;
    }

    // while reads the image
    while (1)
    {
        bytesRead = fread(thebuffer, sizeof(BYTE), 512, f);
        if (thebuffer[0] == 0xff && thebuffer[1] == 0xd8 && thebuffer[2] == 0xff && (thebuffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                // if counter equals 0, image gets modified
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(thebuffer, sizeof(BYTE), bytesRead, img);
                counter++;
            }
            else
            {
                // if counter equals 1 or higher, closes the img
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(thebuffer, sizeof(BYTE), bytesRead, img);
                counter++;
            }
        }

        else if (counter != 0)
        {
            // midify the file if counter is not 0
            fwrite(thebuffer, sizeof(BYTE), bytesRead, img);
            // if bytes that were readed equals 0, it closes all.
            if (bytesRead == 0)
            {
                fclose(img);
                fclose(f);
                return 0;
            }
        }
    }
    fclose(img);
    fclose(f);

}