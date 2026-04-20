long getMedian(int sample_size)
{
  long samples[sample_size];

  for (int i = 0; i < sample_size; i++)
  {
    samples[i] = myScale.read();
  }
  // Sort based from lowest to highest
  for (int i = 0; i < sample_size - 1; i++)
  {
    for (int j = i + 1; j < sample_size; j++)
    {
      if (samples[j] < samples[i])
      {
        long temp = samples[i];
        samples[i] = samples[j];
        samples[j] = temp;
      }
    }
  }
  return values[samples / 2];
}