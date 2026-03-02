check:
	@if [ -f $(BUILD_DIR)/$(TARGET).hex ]; then \
		echo "Build encontrada em $(BUILD_DIR)"; \
	else \
		echo "Nenhuma build encontrada"; \
		pio run -t upload; \
	fi


plaformio:
		
	@pio monitor -m 115200 /dev/ttyUSB0 
