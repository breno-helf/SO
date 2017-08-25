void ShortestJobFirst (&v, &cur_pos, &cur_size, &complete_process, &context_change) {
    for(int i = 0; i < numPross; i++)
        createBlockedPthread(v[i]);
    for(int i = 0; i < numPross; i++)
        RunPthread(v[i]);
}