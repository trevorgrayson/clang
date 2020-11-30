# USB driver: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
# https://arduino.github.io/arduino-cli/getting-started/
# SSD1306 code from: https://github.com/ThingPulse/esp8266-oled-ssd1306
PROJECT=phone.bin
BUILD_DIR=build/Heltec-esp8266.esp8266.generic
BAUD?=115200
PORT?=/dev/cu.SLAB_USBtoUART
ARDUINO_CONF=arduino-cli.yaml
ACLI=arduino-cli
# --config-file $(ARDUINO_CONF)

SRCS=$(wildcard *.c **/*.c)

OBJS=$(SRCS:.c=.o)
	
upload: compile
	$(ACLI) upload -p $(PORT) --fqbn Heltec-esp8266:esp8266:generic

compile:
	mkdir -p $(BUILD_DIR)
	$(ACLI) compile --output-dir $(BUILD_DIR) --fqbn Heltec-esp8266:esp8266:generic 
	@ # heltec:esp8266:wifi_kit_8 

setup:
ifeq (,$(wildcard $(HOME)/.arduino15/arduino-cli.yaml))
	$(ACLI) config init
endif
	$(ACLI) core update-index --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
	$(ACLI) core update-index --additional-urls https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.1/package_heltec_esp8266_index.json
	$(ACLI) core install esp8266:esp8266
	$(ACLI) core install Heltec-esp8266:esp8266
	# $(ACLI) lib install ssd1306

boards:
	$(ACLI) board list

search:
	# $(ACLI) lib install FTDebouncer
	$(ACLI) lib search SSD1306Wire
	# "ESP8266 and ESP32 OLED driver for SSD1306 displays"

monitor:
	@echo "Ctrl a, Ctrl \ to disconnect"
	screen $(PORT) $(BAUD)

render:
	mogrify -resize 14x14 +dither -format xbm images/*.png
	cat images/*.xbm > images.h

test: compile

clean:
	find . -name '*.o' -delete
	find images -name '*.xbm' -delete
