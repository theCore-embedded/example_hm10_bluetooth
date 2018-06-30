/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//! \file
//! \brief HM-10 usage example

// For ecl::hm10_driver
#include <ecl/core_generated.hpp>
// For ecl::cout and ecl::endl
#include <ecl/iostream.hpp>

// Basic, low-level initialization
extern "C" void board_init()
{
    // Here, we only initialize GPIOs.
    gpio_init_generated();
}

int main()
{
    // Data to send and its size.
    uint8_t tx[] = "Hello, World!\r\n";

    // Buffer for incoming data.
    uint8_t rx[256];

    // Greeting.
    ecl::cout << "Starting HM-10 Bluetooth example..." << ecl::endl;

    // Initialize HM10 driver.
    ecl::hm10_driver::init();

    // Set PIN to 000000 during pairing.
    ecl::hm10_driver::set_pin(0);

    while (1) {
        size_t tx_size = sizeof(tx);
        size_t rx_size = sizeof(rx) - 1; // Reserve one byte for NUL-terminator

        // Send data via Bluetooth.
        // When smartphone connected, data will be displayed as plain string.
        ecl::hm10_driver::data_send(tx, tx_size);

        // Display how much data was sent.
        ecl::cout << "Bytes sent: " << tx_size << ecl::endl;

        // Receive some data
        ecl::hm10_driver::data_recv(rx, rx_size, std::chrono::seconds(5));
        rx[rx_size] = 0; // NUL-terminate payload

        // Display how much data was received.
        ecl::cout << "Bytes received: " << rx_size << ecl::endl;

        if (rx_size > 0) {
            // Display payload
            ecl::cout << reinterpret_cast<const char*>(rx) << ecl::endl;
        }
    }

    return 0;
}
