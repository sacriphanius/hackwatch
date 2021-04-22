#include "tile-scanner.h"

tile_t scanner_tile;

#define TAG "[tile::wifi::scanner]"

wifiscan_t g_wifiscan;

void scanner_event_handler(wifiscan_event_t event)
{
  wifi_ap_t *p_ap;

  if (event == WS_EVENT_SELECTED)
  {
    /* Process selected AP. */
    p_ap = wifiscan_get_selected(&g_wifiscan);
    ESP_LOGI(TAG, "AP selected: %s", p_ap->essid);

    /* Switch to the next screen (bottom). */
    tile_apinfo_set_ap(p_ap);
    ui_go_down();
  }
}

tile_t *tile_scanner_init(void)
{
  /* Initialize our tile. */
  tile_init(&scanner_tile, NULL);

  /* Add a wifiscan widget. */
  wifiscan_init(&g_wifiscan, &scanner_tile, 5, 5, 230, 230);
  wifiscan_set_event_handler(&g_wifiscan, scanner_event_handler);

  /* Return our tile. */
  return &scanner_tile;
}