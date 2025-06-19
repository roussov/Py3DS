# Toolchain DevKitPro pour 3DS
# Assure-toi que DEVKITPRO et DEVKITARM sont bien configurés dans l’environnement

# Compilateur et outils
CC       := $(DEVKITARM)/bin/arm-none-eabi-gcc
CXX      := $(DEVKITARM)/bin/arm-none-eabi-g++
AS       := $(DEVKITARM)/bin/arm-none-eabi-as
LD       := $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY  := $(DEVKITARM)/bin/arm-none-eabi-objcopy
OBJDUMP  := $(DEVKITARM)/bin/arm-none-eabi-objdump
SIZE     := $(DEVKITARM)/bin/arm-none-eabi-size

# Répertoires sources et build
SRC_DIR  := src
INC_DIR  := include
BUILD_DIR:= build

# Nom du projet/binaire
TARGET   := my3dsapp

# Fichiers sources (recursif dans src/)
SRCS     := $(shell find $(SRC_DIR) -name '*.c')
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Flags compilation
CFLAGS  := -marm -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp
CFLAGS += -Wall -Wextra -Wshadow -Wformat=2 -Winit-self -Wuninitialized -Wcast-align
CFLAGS += -Os -fomit-frame-pointer
CFLAGS += -DARM11 -D__3DS__
CFLAGS += -I$(INC_DIR) -I$(DEVKITPRO)/libctru/include
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -fno-strict-aliasing

# Flags linking
LDFLAGS := -specs=3dsx.specs -Wl,--gc-sections
LDFLAGS += -L$(DEVKITPRO)/libctru/lib -lctru -lm

# Générer fichiers nécessaires dans build dir
$(shell mkdir -p $(BUILD_DIR))

# Règles principales
all: $(TARGET).3dsx

# Construire le fichier ELF
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Convertir ELF en 3DSX
$(TARGET).3dsx: $(TARGET).elf
	$(DEVKITPRO)/3ds/3dsxtool/3dsxtool $< $@

# Compilation des sources en objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(TARGET).elf $(TARGET).3dsx

.PHONY: all clean
