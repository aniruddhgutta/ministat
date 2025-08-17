#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <alsa/asoundlib.h>

static const char *ic[] = { "󰝟", "󰕿", "󰖀", "󰕾" };
static const char *dev = "default";

int
volume(char *buf, size_t len, const char *mixname)
{
  snd_mixer_t *mixer = NULL;
  snd_mixer_selem_id_t *mixid = NULL;
  snd_mixer_elem_t *elem = NULL;
  long min = 0, max = 0, volume = -1;
  int sw1 = 1, sw2 = 1, perc;
  const char *icon;

  if (!mixname) return snprintf(buf, len, "n/a");

  if (snd_mixer_open(&mixer, 0)) return snprintf(buf, len, "n/a");
  if (snd_mixer_attach(mixer, dev) ||
    snd_mixer_selem_register(mixer, NULL, NULL) ||
    snd_mixer_load(mixer)) goto cleanup;

  snd_mixer_selem_id_alloca(&mixid);
  snd_mixer_selem_id_set_name(mixid, mixname);
  snd_mixer_selem_id_set_index(mixid, 0);

  if (!(elem = snd_mixer_find_selem(mixer, mixid))) goto cleanup;
  if (snd_mixer_selem_get_playback_volume_range(elem, &min, &max)) goto cleanup;
  if (snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume)) goto cleanup;
  snd_mixer_selem_get_playback_switch(elem, 0, &sw1);
  snd_mixer_selem_get_playback_switch(elem, 1, &sw2);

cleanup:
  snd_mixer_free(mixer);
  snd_mixer_detach(mixer, dev);
  snd_mixer_close(mixer);

  if (volume == -1) return snprintf(buf, len, "n/a");
  if (!(sw1 || sw2)) return snprintf(buf, len, "%s 0", ic[0]);

  perc = (int)((volume - min) * 100.0 / (max - min) + 0.5);
  if (perc == 0)
    icon = ic[1];
  else if (perc <= 49)
    icon = ic[2];
  else
    icon = ic[3];

  return snprintf(buf, len, "%s %d", icon, perc);
}
